/*
 * Xournal++
 *
 * This file is part of the Xournal UnitTests
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#include "gui/dialog/SettingsDialogPaletteTab.h"

#include "GtkTest.h"
#include "config-test.h"

void createAndSetupWidgets(GtkApplication* app, GtkGrid** grid, GtkLabel** mainLabel, GtkListBox** optionsList) {
    GtkWidget* window = gtk_application_window_new(app);

    *grid = GTK_GRID(gtk_grid_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(*grid));

    *mainLabel = GTK_LABEL(gtk_label_new(""));
    *optionsList = GTK_LIST_BOX(gtk_list_box_new());
    gtk_container_add(GTK_CONTAINER(*grid), GTK_WIDGET(*mainLabel));
    gtk_container_add(GTK_CONTAINER(*grid), GTK_WIDGET(*optionsList));
}

class UnrenderedPaletteTabTest: public GtkTest {
    void runTest(GtkApplication* app) override {
        GtkGrid* grid = nullptr;
        GtkLabel* mainLabel = nullptr;
        GtkListBox* optionsList = nullptr;
        createAndSetupWidgets(app, &grid, &mainLabel, &optionsList);

        const fs::path palettePath{GET_TESTFILE("palettes/xournalpp.gpl")};

        const std::vector<fs::path> paletteDirectories{palettePath.parent_path()};
        SettingsDialogPaletteTab paletteTab{mainLabel, optionsList, paletteDirectories};
        EXPECT_EQ(paletteTab.getSelectedPalette(), std::nullopt);
    }
};
TEST_F(UnrenderedPaletteTabTest, unrenderedPaletteTabShouldYieldNoSelectedPalette) {}

class RenderedPaletteTabTest: public GtkTest {
    void runTest(GtkApplication* app) override {
        GtkGrid* grid = nullptr;
        GtkLabel* mainLabel = nullptr;
        GtkListBox* optionsList = nullptr;
        createAndSetupWidgets(app, &grid, &mainLabel, &optionsList);

        const fs::path palettePath{GET_TESTFILE("palettes/xournalpp.gpl")};

        const std::vector<fs::path> paletteDirectories{palettePath.parent_path()};
        SettingsDialogPaletteTab paletteTab{mainLabel, optionsList, paletteDirectories};
        paletteTab.renderPaletteTab(palettePath);
        EXPECT_EQ(palettePath.u8string(), paletteTab.getSelectedPalette().value().u8string());
    }
};
TEST_F(RenderedPaletteTabTest, renderedPaletteTabShouldNotChangeSelectedColorPalette) {}
