#pragma once

// How eligible is a given single monster to recite?
enum recite_eligibility
{
    RE_INELIGIBLE,      // Can never be recited to.
    RE_TOO_STRONG,      // Could be recited to at higher power.
    RE_RECITE_TIMER,    // Already affected by ongoing recitation.
    RE_ELIGIBLE,        // Can be recited to.
};
