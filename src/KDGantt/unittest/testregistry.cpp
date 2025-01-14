/****************************************************************************
**
** This file is part of the KD Chart library.
**
** SPDX-FileCopyrightText: 2001-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDChart OR LicenseRef-KDAB-KDChart-US
**
** Licensees holding valid commercial KD Chart licenses may use this file in
** accordance with the KD Chart Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not
** clear to you.
**
****************************************************************************/

#ifndef KDAB_NO_UNIT_TESTS

#include "testregistry.h"

#include "test.h"

#include <memory>
#include <iostream>
#include <iomanip>
#include <cassert>

KDAB::UnitTest::TestRegistry::TestRegistry()
    : mTests()
{
}

KDAB::UnitTest::TestRegistry::~TestRegistry()
{
}

KDAB::UnitTest::TestRegistry *KDAB::UnitTest::TestRegistry::mSelf = nullptr;

// static
KDAB::UnitTest::TestRegistry *KDAB::UnitTest::TestRegistry::instance()
{
    if (!mSelf)
        mSelf = new TestRegistry;
    return mSelf;
}

// static
void KDAB::UnitTest::TestRegistry::deleteInstance()
{
    delete mSelf;
    mSelf = nullptr;
}

void KDAB::UnitTest::TestRegistry::registerTestFactory(const TestFactory *tf, const char *group)
{
    assert(tf);
    mTests[group].push_back(tf);
}

unsigned int KDAB::UnitTest::TestRegistry::run() const
{
    unsigned int failed = 0;
    for (std::map<std::string, std::vector<const TestFactory *>>::const_iterator g = mTests.begin(); g != mTests.end(); ++g) {
        std::cerr << "===== GROUP \"" << g->first << "\" =========" << std::endl;
        for (std::vector<const TestFactory *>::const_iterator it = g->second.begin(); it != g->second.end(); ++it) {
            std::unique_ptr<Test> t((*it)->create());
            assert(t.get());
            std::cerr << "  === \"" << t->name() << "\" ===" << std::endl;
            t->run();
            std::cerr << "    Succeeded: " << std::setw(4) << t->succeeded()
                      << ";  failed: " << std::setw(4) << t->failed() << std::endl;
            failed += t->failed();
        }
    }
    return failed;
}

unsigned int KDAB::UnitTest::TestRegistry::run(const char *group) const
{
    assert(group);
    assert(*group);
    unsigned int failed = 0;
    const std::map<std::string, std::vector<const TestFactory *>>::const_iterator g = mTests.find(group);
    if (g == mTests.end()) {
        std::cerr << "ERROR: No such group \"" << group << "\"" << std::endl;
        return 1;
    }
    std::cerr << "===== GROUP \"" << g->first << "\" =========" << std::endl;
    for (std::vector<const TestFactory *>::const_iterator it = g->second.begin(); it != g->second.end(); ++it) {
        std::unique_ptr<Test> t((*it)->create());
        assert(t.get());
        std::cerr << "  === \"" << t->name() << "\" ===" << std::endl;
        t->run();
        std::cerr << "    Succeeded: " << t->succeeded() << ";  failed: " << t->failed() << std::endl;
        failed += t->failed();
    }
    return failed;
}

KDAB::UnitTest::Runner::~Runner()
{
    TestRegistry::deleteInstance();
}

unsigned int KDAB::UnitTest::Runner::run(const char *group) const
{
    if (group && *group)
        return TestRegistry::instance()->run(group);
    else
        return TestRegistry::instance()->run();
}

#endif // KDAB_NO_UNIT_TESTS
