/*
 * Xournal++
 *
 * Xournal main entry, commandline parser
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once


#include <glib.h>

#include "gui/GladeSearchpath.h"
class GladeSearchpath;

namespace XournalMain {
auto run(int argc, char** argv) -> int;

void initResourcePath(GladeSearchpath* gladePath, std::string_view relativePathAndFile, bool failIfNotFound = true);
}  // namespace XournalMain
