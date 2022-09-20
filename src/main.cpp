/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "commandlineparser.h"
#include "leakdetector.h"

#include "telemetry.h"

int main(int argc, char* argv[]) {
#ifdef MVPN_DEBUG
  LeakDetector leakDetector;
  Q_UNUSED(leakDetector);
#endif
  Telemetry::recordAppStartTimestamp();

  CommandLineParser clp;
  return clp.parse(argc, argv);
}
