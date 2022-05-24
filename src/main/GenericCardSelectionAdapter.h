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

/* Keyple Card Generic */
#include "CardSelectorAdapter.h"
#include "GenericCardSelection.h"

/* Calypsonet Terminal Card */
#include "CardSelectionResponseApi.h"
#include "CardSelectionSpi.h"
#include "SmartCardSpi.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card;
using namespace calypsonet::terminal::card::spi;

/**
 * (package-private)<br>
 * Implementation of a generic {@link CardSelection}.
 *
 * @since 2.0.0
 */
class GenericCardSelectionAdapter final : public GenericCardSelection, public CardSelectionSpi {
public:
    /**
     * (package-private) Creates an instance.
     *
     * @since 2.0.0
     */
    GenericCardSelectionAdapter();

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::shared_ptr<CardSelectionRequestSpi> getCardSelectionRequest() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::shared_ptr<SmartCardSpi> parse(
        const std::shared_ptr<CardSelectionResponseApi> cardSelectionResponse) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& filterByCardProtocol(const std::string& cardProtocol) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& filterByPowerOnData(const std::string& powerOnDataRegex) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& filterByDfName(const std::vector<uint8_t>& aid) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& filterByDfName(const std::string& aid) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& setFileOccurrence(const FileOccurrence fileOccurrence) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& setFileControlInformation(
        const FileControlInformation fileControlInformation) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    GenericCardSelection& addSuccessfulStatusWord(const int statusWord) override;

private:
    /**
     *
     */
    static const int AID_MIN_LENGTH;

    /**
     *
     */
    static const int AID_MAX_LENGTH;

    /**
     *
     */
    std::shared_ptr<CardSelectorAdapter> mCardSelector;
};

}
}
}
