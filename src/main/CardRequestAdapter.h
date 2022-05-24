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
#include <vector>

/* Calypsonet Terminal Card */
#include "CardRequestSpi.h"

namespace keyple {
namespace card {
namespace generic {

using namespace calypsonet::terminal::card::spi;

/**
 * (package-private)<br>
 * This POJO contains an ordered list of {@link ApduRequestSpi} and the associated status word check
 * policy.
 *
 * @since 2.0.0
 */
class CardRequestAdapter final : public CardRequestSpi {
public:
    /**
     * Builds a card request with a list of {@link ApduRequestSpi } and the flag indicating the
     * expected response checking behavior.
     *
     * <p>When the status word verification is enabled, the transmission of the APDUs must be
     * interrupted as soon as the status word of a response is unexpected.
     *
     * @param apduRequests A not empty list.
     * @param stopOnUnsuccessfulStatusWord True if the transmission must be stopped when an unexpected
     *     status word is received.
     * @since 2.0.0
     */
    CardRequestAdapter(const std::vector<std::shared_ptr<ApduRequestSpi>>& apduRequests, 
                       const bool stopOnUnsuccessfulStatusWord);

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    const std::vector<std::shared_ptr<ApduRequestSpi>>& getApduRequests() const override;

    /**
     * {@inheritDoc}
     *
     * @since 2.0.0
     */
    bool stopOnUnsuccessfulStatusWord() const override;

private:
    /**
     * 
     */
    const std::vector<std::shared_ptr<ApduRequestSpi>> mApduRequests;
    
    /**
     * 
     */
    const bool mStopOnUnsuccessfulStatusWord;
};

}
}
}
