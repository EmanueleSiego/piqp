// This file is part of PIQP.
//
// Copyright (c) 2024 EPFL
//
// This source code is licensed under the BSD 2-Clause License found in the
// LICENSE file in the root directory of this source tree.

#include <benchmark/benchmark.h>

#include "piqp/piqp.hpp"
#include "piqp/utils/io_utils.hpp"

using T = double;
using I = int;

static void BM_CHAIN_SQP_KKT_FULL(benchmark::State& state)
{
    piqp::sparse::Model<T, I> model = piqp::load_sparse_model<T, I>("data/chain_mass_sqp.mat");

    piqp::SparseSolver<T, I, piqp::KKTMode::KKT_FULL> solver;
    solver.setup(model.P, model.c, model.A, model.b, model.G, model.h, model.x_lb, model.x_ub);

    for (auto _ : state)
    {
        solver.update(model.P, model.c, model.A, model.b, model.G, model.h, model.x_lb, model.x_ub);
        solver.solve();
    }
}

static void BM_CHAIN_SQP_KKT_ALL_ELIMINATED(benchmark::State& state)
{
    piqp::sparse::Model<T, I> model = piqp::load_sparse_model<T, I>("data/chain_mass_sqp.mat");

    piqp::SparseSolver<T, I, piqp::KKTMode::KKT_ALL_ELIMINATED> solver;
    solver.setup(model.P, model.c, model.A, model.b, model.G, model.h, model.x_lb, model.x_ub);

    for (auto _ : state)
    {
        solver.update(model.P, model.c, model.A, model.b, model.G, model.h, model.x_lb, model.x_ub);
        solver.solve();
    }
}

BENCHMARK(BM_CHAIN_SQP_KKT_FULL)->Unit(benchmark::kMicrosecond);
BENCHMARK(BM_CHAIN_SQP_KKT_ALL_ELIMINATED)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
