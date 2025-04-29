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

#include "keypop/reader/selection/spi/CardSelectionExtension.hpp"

namespace keyple {
namespace card {
namespace generic {

using keypop::reader::selection::spi::CardSelectionExtension;

/**
 * Card specific CardSelectionExtension providing means to add successful status
 * word.
 *
 * @since 3.0.0
 */
class GenericCardSelectionExtension : public CardSelectionExtension {
public:
    /**
     *
     */
    virtual ~GenericCardSelectionExtension() = default;

    /**
     * Adds a status word to the list of those that should be considered
     * successful for the Select Application APDU.
     *
     * <p>Note: initially, the list contains the standard successful status word
     * 9000h.
     *
     * @param statusWord A positive int &le; {@code FFFFh}.
     * @return The current instance.
     * @since 2.0.0
     */
    virtual GenericCardSelectionExtension&
    addSuccessfulStatusWord(const int statusWord)
        = 0;
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
