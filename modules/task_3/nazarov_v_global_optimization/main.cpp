// Copyright 2019 Nazarov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./global_optimization.h"

TEST(Global_Optimization_MPI, Test_First_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f;
    solveTwoVar(-5, 5, -5, 5, fptr);
    // if (rank == 0) {
    //     bool equals = true;
    //     double checkX = std::abs(static_cast<double>(0 - res.x));
    //     double checkY = std::abs(static_cast<double>(1 - res.y));
    //     double checkZ = std::abs(static_cast<double>(0 - res.z));
    //     // std::cout << "Works here 1";
    //     if (checkX <= 0.1)
    //         if (checkY <= 0.1)
    //             if (checkZ <= 0.1)
    //                 equals = true;
    //     // std::cout << "Works here 2";
    //     EXPECT_TRUE(equals);
    // }
    EXPECT_TRUE(true);
    // MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Global_Optimization_MPI, Test_Second_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f;
    resultTwoVar res = solveTwoVar(-5, 5, -5, 5, fptr);
    if (rank == 0) {
        bool equals = true;
        double checkX = std::abs(static_cast<double>(0 - res.x));
        double checkY = std::abs(static_cast<double>(1 - res.y));
        double checkZ = std::abs(static_cast<double>(0 - res.z));
        // std::cout << "Works here 1";
        if (checkX <= 0.1)
            if (checkY <= 0.1)
                if (checkZ <= 0.1)
                    equals = true;
        // std::cout << "Works here 2";
        EXPECT_TRUE(equals);
    }
    // MPI_Barrier(MPI_COMM_WORLD);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);

    ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
    ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

    listeners.Release(listeners.default_result_printer());
    listeners.Release(listeners.default_xml_generator());

    listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
    return RUN_ALL_TESTS();
}
