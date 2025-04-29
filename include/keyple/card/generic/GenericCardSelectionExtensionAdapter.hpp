/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
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
#include <vector>

#include "keyple/card/generic/GenericCardSelectionExtension.hpp"
#include "keypop/card/CardSelectionResponseApi.hpp"
#include "keypop/card/spi/CardSelectionExtensionSpi.hpp"
#include "keypop/card/spi/CardSelectionRequestSpi.hpp"
#include "keypop/card/spi/SmartCardSpi.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::card::CardSelectionResponseApi;
using keypop::card::spi::CardSelectionExtensionSpi;
using keypop::card::spi::CardSelectionRequestSpi;
using keypop::card::spi::SmartCardSpi;

/**
 * Implementation of GenericCardSelectionExtension.
 *
 * @since 2.0.0
 */
class GenericCardSelectionExtensionAdapter
: public GenericCardSelectionExtension,
  public CardSelectionExtensionSpi {
public:
    /**
     * Creates an instance.
     *
     * @since 2.0.0
     */
    GenericCardSelectionExtensionAdapter();

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<CardSelectionRequestSpi>
    getCardSelectionRequest() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    std::shared_ptr<SmartCardSpi>
    parse(const std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse)
        const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelectionExtension&
    addSuccessfulStatusWord(const int statusWord) override;

private:
    /**
     *
     */
    static const int DEFAULT_SUCCESSFUL_CODE;

    /**
     *
     */
    std::vector<int> mSuccessfulSelectionStatusWords;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
