#pragma once
#ifndef SHEATH_CLOSURE_H
#define SHEATH_CLOSURE_H

#include "component.hxx"

/// 2D closure, modelling currents through a sheath
///
/// This should only be used where one grid cell is used in y (ny=1).
/// For domains with multiple Y points, use sheath_boundary
struct SheathClosure : public Component {
  /// Inputs
  ///  - units
  ///    - meters    Length normalisation
  ///  - <name>
  ///    - connection_length    Parallel connection length in meters
  ///
  SheathClosure(std::string name, Options &options, Solver *);

  /// Inputs
  /// - fields
  ///   - phi      Electrostatic potential
  ///
  /// Optional inputs
  /// - species
  ///   - e
  ///     - density
  ///
  /// Modifies
  /// - species
  ///   - e
  ///     - density_source   (If density present)
  /// - fields
  ///   - DivJdia     Divergence of current
  ///
  void transform(Options &state) override;
private:
  BoutReal L_par; // Normalised connection length

  BoutReal sheath_gamma; // Sheath heat transmission coefficient

  BoutReal offset; // Potential at which the sheath current is zero
};

namespace {
RegisterComponent<SheathClosure>
    registercomponentsheathclosure("sheath_closure");
}


#endif // SHEATH_CLOSURE_H
