#include "SettingsDialogPaletteTab.h"

#include "gui/toolbarMenubar/icon/ColorIcon.h"
#include "util/PathUtil.h"
#include "util/gtk4_helper.h"
#include "util/i18n.h"

static const char* const G_OBJECT_PALETTE_PATH = "xournalpp.palettePath";


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto colorize(const std::string& text, const std::string& color) -> std::string {
    return std::string{"<span foreground=\""} + color + std::string{"\">"} + text + std::string{"</span>"};
}

auto pathLink(const fs::path& path) -> std::string {
    return FS(_F("<a href=\"file://{1}\">{1}</a>") % path.u8string());
}

void setGObjectPalettePath(GObject* gObject, const fs::path& path) {
    g_object_set_data(gObject, G_OBJECT_PALETTE_PATH, (gpointer)&path);
}

auto getGObjectPalettePath(GObject* gObject) -> fs::path {
    auto* pathPointer = (fs::path*)g_object_get_data(gObject, G_OBJECT_PALETTE_PATH);
    return *pathPointer;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

constexpr auto UI_FILE = "paletteSettings.glade";
constexpr auto UI_PANEL_NAME = "paletteSettingsPanel";

SettingsDialogPaletteTab::SettingsDialogPaletteTab(GladeSearchpath* gladeSearchPath,
                                                   const std::vector<fs::path>& paletteDirectories):
        builder(gladeSearchPath, UI_FILE) {
    colorPaletteExplainLabel = GTK_LABEL(builder.get("colorPaletteExplainLabel"));
    paletteListBox = GTK_LIST_BOX(builder.get("paletteListBox"));
    panel = GTK_SCROLLED_WINDOW(builder.get(UI_PANEL_NAME));
    renderColorPaletteExplainLabel();
    setAllPaletteFilePaths(paletteDirectories);
}

void SettingsDialogPaletteTab::renderPaletteTab(const fs::path& currentlySetPalettePath) {
    GtkListBox* lb = paletteListBox;
    if (allPaletteFilePaths.empty()) {
        renderNoPaletteFoundDisclaimer(lb);
        return;
    }

    for (const fs::path& p: allPaletteFilePaths) {
        GtkWidget* listBoxRow = renderPaletteListBoxRow(lb, p);

        if (p == currentlySetPalettePath)
            gtk_list_box_select_row(GTK_LIST_BOX(lb), GTK_LIST_BOX_ROW(listBoxRow));
    }
    gtk_widget_show_all(GTK_WIDGET(lb));
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

auto SettingsDialogPaletteTab::renderPaletteListBoxRow(GtkListBox* lb, const fs::path& p) -> GtkWidget* {
    Palette palette{p};
    GtkWidget* listBoxRow = nullptr;

    try {
        palette.load();
        listBoxRow = newPaletteListBoxRow(palette);
    } catch (const std::exception& e) {
        listBoxRow = newErrorListBoxRow(p, e.what());
    }
    setGObjectPalettePath(G_OBJECT(listBoxRow), p);

    gtk_list_box_prepend(lb, listBoxRow);
    return listBoxRow;
}

void SettingsDialogPaletteTab::renderColorPaletteExplainLabel() const {
    gtk_label_set_label(colorPaletteExplainLabel, FS(_F("<i>The palettes shown below are obtained from:\n"
                                                        "   - Built-in palettes: {1}\n"
                                                        "   - User palettes: {2}.\n</i>") %
                                                     pathLink(Util::getBuiltInPaletteDirectoryPath()) %
                                                     pathLink(Util::getCustomPaletteDirectoryPath()))
                                                          .c_str());
    gtk_label_set_use_markup(colorPaletteExplainLabel, true);
}

void SettingsDialogPaletteTab::renderNoPaletteFoundDisclaimer(GtkListBox* lb) {
    GtkWidget* listBoxRow = gtk_list_box_row_new();
    GtkWidget* label = gtk_label_new("<span foreground=\"red\">"
                                     "No palette files (i.e. with extension .gpl) could be found.\n"
                                     "Using the default until another palette is configured."
                                     "</span>");
    gtk_label_set_use_markup(GTK_LABEL(label), true);

    gtk_list_box_append(GTK_LIST_BOX(listBoxRow), label);
    gtk_list_box_row_set_activatable(GTK_LIST_BOX_ROW(listBoxRow), FALSE);
    gtk_list_box_row_set_selectable(GTK_LIST_BOX_ROW(listBoxRow), FALSE);

    gtk_list_box_prepend(lb, listBoxRow);
}

// use list of fs::path as input
void SettingsDialogPaletteTab::setAllPaletteFilePaths(const std::vector<fs::path>& paletteDirectories) {
    for (const fs::path& paletteDirectory: paletteDirectories) {
        std::vector<fs::path> const files = Util::listFilesSorted(paletteDirectory);
        for (const fs::path& paletteFile: files) {
            if (paletteFile.extension() == ".gpl") {
                allPaletteFilePaths.push_back(paletteFile);
            }
        }
    }
}

auto SettingsDialogPaletteTab::getSelectedPalette() -> std::optional<fs::path> {
    GtkListBoxRow* selected_listbox_row = gtk_list_box_get_selected_row(paletteListBox);
    if (allPaletteFilePaths.empty()) {
        return {};
    }
    if (!G_IS_OBJECT(selected_listbox_row)) {
        return {};
    }

    return getGObjectPalettePath(G_OBJECT(selected_listbox_row));
}

auto SettingsDialogPaletteTab::newErrorListBoxRow(const fs::path& palettePath, const std::string& error) -> GtkWidget* {
    GtkWidget* listBoxRow = gtk_list_box_row_new();
    GtkWidget* rowContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_list_box_append(GTK_LIST_BOX(listBoxRow), rowContent);

    std::string const formattedError = colorize("Error: " + error, "red");
    GtkWidget* text = newPaletteTextBox(formattedError, palettePath);
    gtk_box_append(GTK_BOX(rowContent), text);

    return listBoxRow;
}

auto SettingsDialogPaletteTab::newPaletteListBoxRow(Palette& palette) -> GtkWidget* {
    GtkWidget* listBoxRow = gtk_list_box_row_new();
    GtkWidget* rowContent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    gtk_list_box_append(GTK_LIST_BOX(listBoxRow), rowContent);

    std::string const paletteName = palette.getHeader(std::string{"Name"});
    GtkWidget* text = nullptr;
    if (paletteName.empty())
        text = newPaletteTextBox(std::string{"<i>Palette has no Name</i>"}, palette.getFilePath());
    else
        text = newPaletteTextBox(paletteName, palette.getFilePath().u8string());
    gtk_box_append(GTK_BOX(rowContent), text);

    GtkWidget* colorIcons = newPaletteColorIconsBox(palette);
    gtk_widget_set_hexpand(colorIcons, true);
    gtk_box_append(GTK_BOX(rowContent), colorIcons);

    return listBoxRow;
}

auto SettingsDialogPaletteTab::newPaletteTextBox(const std::string& mainContent, const fs::path& path) -> GtkWidget* {
    GtkWidget* textBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);

    GtkWidget* mainLabel = gtk_label_new(mainContent.c_str());
    gtk_widget_set_halign(mainLabel, GTK_ALIGN_START);
    gtk_label_set_use_markup(GTK_LABEL(mainLabel), true);
    gtk_box_append(GTK_BOX(textBox), mainLabel);

    std::string const secondaryInformation = std::string{"└─ "} + path.u8string();
    GtkWidget* secondaryLabel = gtk_label_new(secondaryInformation.c_str());
    gtk_widget_set_halign(secondaryLabel, GTK_ALIGN_START);
    gtk_label_set_use_markup(GTK_LABEL(secondaryLabel), true);
    gtk_box_append(GTK_BOX(textBox), secondaryLabel);

    return textBox;
}

auto SettingsDialogPaletteTab::newPaletteColorIconsBox(const Palette& palette) -> GtkWidget* {
    GtkWidget* colors = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
    for (unsigned long i = 0; i < palette.size(); i++) {
        const NamedColor& namedColor = palette.getColorAt(i);
        const Color c = namedColor.getColor();
        GtkWidget* icon = ColorIcon::newGtkImage(c, 16, true);
        gtk_box_append(GTK_BOX(colors), icon);
    }
    gtk_widget_set_halign(colors, GTK_ALIGN_END);
    return colors;
}
