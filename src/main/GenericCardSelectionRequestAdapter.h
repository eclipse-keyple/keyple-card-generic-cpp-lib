/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <memory>

/* Calypsonet Terminal Card */
#include "CardSelectionRequestSpi.h"
#include "CardSelectorSpi.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card::spi;

/**
 * (package-private)<br>
 * Implementation of {@link CardSelectionRequestSpi}
 *
 * @since 2.0.0
 */
class GenericCardSelectionRequestAdapter final : public CardSelectionRequestSpi {
public:
    /**
     * Builds a card selection request to open a logical channel with additional APDUs to be sent
     * after the selection step.
     *
     * @param cardSelector The card selector.
     * @since 2.0.0
     */
    GenericCardSelectionRequestAdapter(std::shared_ptr<CardSelectorSpi> cardSelector);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::shared_ptr<CardSelectorSpi> getCardSelector() const;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::shared_ptr<CardRequestSpi> getCardRequest() const;

private:
    /**
     *
     */
    std::shared_ptr<CardSelectorSpi> mCardSelector;
};

}
}
}
