#include "emp-ot/emp-ot.h"
#include "test/test.h"
using namespace std;

int port, party;
const static int threads = 4;

void test_ferret(int party, NetIO *ios[threads], int64_t num_ot) {
    auto start = clock_start();
    FerretCOT<NetIO> * ferretcot = new FerretCOT<NetIO>(party, threads, ios, true);
    double timeused = time_from(start);
    std::cout << party << "\tsetup\t" << timeused/1000 << "ms" << std::endl;

    // RCOT
    // The RCOTs will be generated at internal memory, and copied to user buffer
    //int64_t num = 1 << num_ot;
    //cout <<"Active FERRET RCOT\t"<<double(num)/test_rcot<FerretCOT<NetIO>>(ferretcot, ios[0], party, num, false)*1e6<<" OTps"<<endl;

    // RCOT inplace
    // The RCOTs will be generated at user buffer
    // Get the buffer size needed by calling byte_memory_need_inplace()



    // Triple generation speed.
    uint64_t batch_size = ferretcot->ot_limit;
    cout <<"Active FERRET RCOT inplace\t"<<double(batch_size)/test_rcot<FerretCOT<NetIO>>(ferretcot, ios[0], party, batch_size, true)*1e6<<" OTps"<<endl;
    delete ferretcot;
}









 // circuit-eval
//int main(int argc, char** argv) {
int circuit_eval() {
    //parse_party_and_port(argv, &party, &port);
    //NetIO* ios[threads];
    //for(int i = 0; i < threads; ++i)
    //    ios[i] = new NetIO(party == ALICE?nullptr:"127.0.0.1",port+i);

    NetIO * io = new NetIO(party==ALICE ? nullptr:"128.10.130.63", port);
    //NetIO * io = new NetIO(party==ALICE ? nullptr:"127.0.0.1", port);
    //int64_t length  = atoi(argv[3]);
    int64_t length  = 2;

    int size1 = 6750;
    int size2 = 2250;
    int size3 = 3000;
    int size4 = 13500;


    block *b1 = new block[length*size1];
    block *delta1 = new block[length*size1];

    block *b2 = new block[length*size2];
    block *delta2 = new block[length*size2];

    block *b3 = new block[length*size3];
    block *delta3 = new block[length*size3];

    block *b4 = new block[length*size4];
    block *delta4 = new block[length*size4];

    PRG prg;
    prg.random_block(delta1, length*size1);
    prg.random_block(b1, length*size1);
    prg.random_block(delta2, length*size2);
    prg.random_block(b2, length*size2);
    prg.random_block(delta3, length*size3);
    prg.random_block(b3, length*size3);
    prg.random_block(delta4, length*size4);
    prg.random_block(b4, length*size4);


    auto start = clock_start();
    for (int i = 0; i < 10; i++){

        io->sync();
        if (party == ALICE) {
            io->send_block(delta1,  length*size1);
            //io->send_block(b, length);
        }else if (party == BOB) {
            io->recv_block(delta1,  length*size1);
            //io->recv_block(b, length);
        }
        io->sync();
        if (party == ALICE) {
            io->recv_block(b1,  length*size1);
            //io->send_block(delta, length);
            //
        }else if (party == BOB) {
            io->send_block(b1,  length*size1);
            //io->recv_block(delta, length);
            //
        }
        io->sync();

        if (party == ALICE) {
            io->send_block(delta2,  length*size2);
            //io->send_block(b, length);
        }else if (party == BOB) {
            io->recv_block(delta2,  length*size2);
            //io->recv_block(b, length);
        }
        io->sync();
        if (party == ALICE) {
            io->recv_block(b2,  length*size2);
            //io->send_block(delta, length);
            //
        }else if (party == BOB) {
            io->send_block(b2,  length*size2);
            //io->recv_block(delta, length);
            //
        }
        io->sync();

        if (party == ALICE) {
            io->send_block(delta3,  length*size3);
            //io->send_block(b, length);
        }else if (party == BOB) {
            io->recv_block(delta3,  length*size3);
            //io->recv_block(b, length);
        }
        io->sync();
        if (party == ALICE) {
            io->recv_block(b3,  length*size3);
            //io->send_block(delta, length);
            //
        }else if (party == BOB) {
            io->send_block(b3,  length*size3);
            //io->recv_block(delta, length);
            //
        }
        io->sync();

        if (party == ALICE) {
            io->send_block(delta4,  length*size4);
            //io->send_block(b, length);
        }else if (party == BOB) {
            io->recv_block(delta4,  length*size4);
            //io->recv_block(b, length);
        }
        io->sync();
        if (party == ALICE) {
            io->recv_block(b4,  length*size4);
            //io->send_block(delta, length);
            //
        }else if (party == BOB) {
            io->send_block(b4,  length*size4);
            //io->recv_block(delta, length);
            //
        }
        io->sync();

    }
    long long t = time_from(start);
    std::cout <<" circuit evaluation time for s=2: " << t <<" \t";
    std::cout <<endl;

    delete io;
    delete[] b1;
    delete[] delta1;
    delete[] b2;
    delete[] delta2;
    delete[] b3;
    delete[] delta3;
    delete[] b4;
    delete[] delta4;

    return 0;
}





//envelope transfer time #length = 780,000
int env_transfer() {
    //parse_party_and_port(argv, &party, &port);
    //NetIO* ios[threads];
    //for(int i = 0; i < threads; ++i)
    //    ios[i] = new NetIO(party == ALICE?nullptr:"127.0.0.1",port+i);

    //NetIO * io = new NetIO(party==ALICE ? nullptr:"127.0.0.1", port);
    NetIO * io = new NetIO(party==ALICE ? nullptr:"128.10.130.63", port);
    //int64_t length  = atoi(argv[3]);
    int64_t length  = 780000;
    //int64_t length  = 1;
    //block *b = new block[length];
    block *delta = new block[length];
    PRG prg;
    prg.random_block(delta, length);
    //prg.random_block(b, length);
    //prg.random_bool(b, length);

    io->sync();
    auto start = clock_start();
    if (party == ALICE) {
        io->send_block(delta, length);
        //io->send_block(b, length);
    }else if (party == BOB) {
        io->recv_block(delta, length);
        //io->recv_block(b, length);
    }
    io->flush();
    long long t = time_from(start);
    std::cout <<"enveloper transfer time: " << t <<" \t";
    std::cout <<endl;

    delete io;
    //delete[] b;
    delete[] delta;

    return 0;
}

int main(int argc, char** argv) {
    parse_party_and_port(argv, &party, &port);

    circuit_eval();
    env_transfer();
    NetIO* ios[threads];
    for(int i = 0; i < threads; ++i)
        ios[i] = new NetIO(party == ALICE?nullptr:"128.10.130.63",port+i);
        //ios[i] = new NetIO(party == ALICE?nullptr:"128.10.130.63",port+i);

    int64_t length = 20;
    if (argc > 3)
        length = atoi(argv[3]);
    test_ferret(party, ios, length);
    for(int i = 0; i < threads; ++i)
        delete ios[i];


}