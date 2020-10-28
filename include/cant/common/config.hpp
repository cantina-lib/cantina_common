//
// Created by binabik on 03/07/2020.
//

#ifndef CANTINA_CONFIG_HPP
#define CANTINA_CONFIG_HPP

#pragma once

#include <cant/common/macro.hpp>
CANTINA_CANT_NAMESPACE_BEGIN

/* ENVELOPES */
static CANT_CONSTEXPR char const * ENVELOPE_FIELD_VELOCITY = "velocity";
static CANT_CONSTEXPR char const * ENVELOPE_FIELD_TONE     = "tone";

static CANT_CONSTEXPR char const * ENVELOPE_TYPE_ADSR = "adsr";
static CANT_CONSTEXPR char const * ENVELOPE_TYPE_FLAT = "flat";

/* CONTROLLERS */
static CANT_CONSTEXPR char const * CONTROLLER_TYPE_DAMPER = "damper";
static CANT_CONSTEXPR char const * CONTROLLER_TYPE_PAN    = "pan";

CANTINA_CANT_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif  // CANTINA_CONFIG_HPP
