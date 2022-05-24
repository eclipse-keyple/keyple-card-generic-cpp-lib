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
#include <string>
#include <vector>

/* Keyple Card Generic */
#include "CardTransactionManager.h"

/* Calypsonet Terminal Card */
#include "ApduRequestSpi.h"
#include "ChannelControl.h"

/* Calypsonet Terminal Reader */
#include "CardReader.h"
#include "SmartCard.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card;
using namespace calypsonet::terminal::card::spi;
using namespace calypsonet::terminal::reader;
using namespace calypsonet::terminal::reader::selection::spi;

/**
 * (package-private)<br>
 * Implementation of CardTransactionManager.
 *
 * @since 2.0.0
 */
class CardTransactionManagerAdapter final : public CardTransactionManager {
public:
    /**
     *
     */
    static const std::string APDU_COMMAND;

    /**
     * (package-private)<br>
     * Creates an instance of CardTransactionManager.
     *
     * @param reader The reader through which the card communicates.
     * @param card The initial card data provided by the selection process.
     * @throw IllegalArgumentException If the card resource or one of its components is null.
     * @since 2.0.0
     */
    CardTransactionManagerAdapter(std::shared_ptr<CardReader> reader,
                                  const std::shared_ptr<SmartCard> card);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(const std::string& apduCommand) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(const std::vector<uint8_t>& apduCommand) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(const uint8_t cla,
                                        const uint8_t ins,
                                        const uint8_t p1,
                                        const uint8_t p2,
                                        const std::vector<uint8_t>& dataIn,
                                        const uint8_t le) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareApdu(const uint8_t cla,
                                        const uint8_t ins,
                                        const uint8_t p1,
                                        const uint8_t p2,
                                        const std::vector<uint8_t>& dataIn) override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    CardTransactionManager& prepareReleaseChannel() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::vector<uint8_t>> processApdusToByteArrays() override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::string> processApdusToHexStrings() override;

private:
    /**
     *
     */
    std::shared_ptr<CardReader> mReader;

    /**
     *
     */
    std::vector<std::shared_ptr<ApduRequestSpi>> mApduRequests;

    /**
     *
     */
    ChannelControl mChannelControl;
};

}
}
}
