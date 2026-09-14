/******************************************************************************
 * Copyright (c) 2026 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#pragma once

#include <memory>

#include "keypop/genericcard/CardTransactionManager.hpp"
#include "keypop/genericcard/GenericCardApiFactory.hpp"
#include "keypop/genericcard/GenericCardSelectionExtension.hpp"
#include "keypop/reader/CardReader.hpp"
#include "keypop/reader/selection/spi/SmartCard.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::genericcard::CardTransactionManager;
using keypop::genericcard::GenericCardApiFactory;
using keypop::genericcard::GenericCardSelectionExtension;
using keypop::reader::CardReader;
using keypop::reader::selection::spi::SmartCard;

/**
 * Adapter of GenericCardApiFactory.
 *
 * @since 4.0.0
 */
class GenericCardApiFactoryAdapter final : public GenericCardApiFactory {
public:
    /**
     * {@inheritDoc}
     *
     * @since 4.0.0
     */
    std::unique_ptr<GenericCardSelectionExtension>
    createGenericCardSelectionExtension() override;

    /**
     * {@inheritDoc}
     *
     * @since 4.0.0
     */
    std::unique_ptr<CardTransactionManager> createCardTransaction(
        const std::shared_ptr<CardReader>& cardReader,
        const std::shared_ptr<SmartCard>& card) override;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
