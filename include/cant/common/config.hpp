//
// Created by binabik on 03/07/2020.
//

#ifndef CANTINA_CONFIG_HPP
#define CANTINA_CONFIG_HPP

#pragma once

namespace cant
{
    /* ENVELOPES */
    static constexpr const char* ENVELOPE_FIELD_VELOCITY = "velocity";
    static constexpr const char* ENVELOPE_FIELD_TONE = "tone";

    static constexpr const char* ENVELOPE_TYPE_ADSR = "adsr";
    static constexpr const char* ENVELOPE_TYPE_FLAT = "flat";

    /* CONTROLLERS */
    static constexpr const char* CONTROLLER_TYPE_DAMPER = "damper";
    static constexpr const char* CONTROLLER_TYPE_PAN = "pan";
}

#endif //CANTINA_CONFIG_HPP
