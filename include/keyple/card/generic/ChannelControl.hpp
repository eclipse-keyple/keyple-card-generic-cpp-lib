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

namespace keyple {
namespace card {
namespace generic {

/**
 * Policy for managing the physical channel after a card request is executed.
 *
 * @since 3.0.0
 */
enum class ChannelControl {
    /**
     * Leaves the physical channel open.
     *
     * @since 3.0.0
     */
    KEEP_OPEN,

    /**
     * Terminates communication with the card.<br>
     * The physical channel closes instantly or a card removal sequence is
     * initiated depending on the observation mode.
     *
     * @since 3.0.0
     */
    CLOSE_AFTER
};

} /* namespace generic */
} /* namespace card */
} /* namespace keyple */
