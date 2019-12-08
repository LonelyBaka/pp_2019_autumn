// Copyright 2019 Nazarov Vladislav
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include "./global_optimization.h"

TEST(Global_Optimization_MPI, Test_First_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f1;
    double prev = MPI_Wtime();
    resultTwoVar res = solveTwoVar(-5, 5, -5, 5, fptr);
    double cur = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Final result parallel, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << res.x << " y: " << res.y << " z: " << res.z << std::endl;
        prev = MPI_Wtime();
        resultTwoVar resEq = solveTwoVarSequential(-5, 5, -5, 5, fptr);
        cur = MPI_Wtime();
        std::cout << "Final result sequential, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << resEq.x << " y: " << resEq.y << " z: " << resEq.z << std::endl;
        ASSERT_TRUE(compareResults(res, resEq, 0.1));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Global_Optimization_MPI, Test_Second_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f2;
    double prev = MPI_Wtime();
    resultTwoVar res = solveTwoVar(-5, 5, -5, 5, fptr);
    double cur = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Final result parallel, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << res.x << " y: " << res.y << " z: " << res.z << std::endl;
        prev = MPI_Wtime();
        resultTwoVar resEq = solveTwoVarSequential(-5, 5, -5, 5, fptr);
        cur = MPI_Wtime();
        std::cout << "Final result sequential, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << resEq.x << " y: " << resEq.y << " z: " << resEq.z << std::endl;
        ASSERT_TRUE(compareResults(res, resEq, 0.1));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Global_Optimization_MPI, Test_Third_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f3;
    double prev = MPI_Wtime();
    resultTwoVar res = solveTwoVar(0, 5, 0, 5, fptr);
    double cur = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Final result parallel, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << res.x << " y: " << res.y << " z: " << res.z << std::endl;
        prev = MPI_Wtime();
        resultTwoVar resEq = solveTwoVarSequential(0, 5, 0, 5, fptr);
        cur = MPI_Wtime();
        std::cout << "Final result sequential, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << resEq.x << " y: " << resEq.y << " z: " << resEq.z << std::endl;
        ASSERT_TRUE(compareResults(res, resEq, 0.1));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Global_Optimization_MPI, Test_Fourth_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f4;
    double prev = MPI_Wtime();
    resultTwoVar res = solveTwoVar(0.1, 5, -5, 5, fptr);
    double cur = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Final result parallel, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << res.x << " y: " << res.y << " z: " << res.z << std::endl;
        prev = MPI_Wtime();
        resultTwoVar resEq = solveTwoVarSequential(0.1, 5, -5, 5, fptr);
        cur = MPI_Wtime();
        std::cout << "Final result sequential, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << resEq.x << " y: " << resEq.y << " z: " << resEq.z << std::endl;
        ASSERT_TRUE(compareResults(res, resEq, 0.1));
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

TEST(Global_Optimization_MPI, Test_Fifth_Function) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double(*fptr)(double, double) = f5;
    double prev = MPI_Wtime();
    resultTwoVar res = solveTwoVar(1.1, 5, 1.1, 5, fptr);
    double cur = MPI_Wtime();
    if (rank == 0) {
        std::cout << "Final result parallel, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << res.x << " y: " << res.y << " z: " << res.z << std::endl;
        prev = MPI_Wtime();
        resultTwoVar resEq = solveTwoVarSequential(1.1, 5, 1.1, 5, fptr);
        cur = MPI_Wtime();
        std::cout << "Final result sequential, time to solve: " << cur-prev << std::endl;
        std::cout << "x: " << resEq.x << " y: " << resEq.y << " z: " << resEq.z << std::endl;
        ASSERT_TRUE(compareResults(res, resEq, 0.1));
    }
    MPI_Barrier(MPI_COMM_WORLD);
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
