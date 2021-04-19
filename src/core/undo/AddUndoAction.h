/*
 * Xournal++
 *
 * Undo action for delete (eraser, delete)
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <set>
#include <string>

#include "PageLayerPosEntry.h"
#include "UndoAction.h"

class Element;

class AddUndoAction: public UndoAction {
public:
    AddUndoAction(const PageRef& page, bool eraser);

public:
    bool undo(Control*) override;
    bool redo(Control*) override;

    void addElement(Layer* layer, Element* e, int pos);

    std::string getText() override;

private:
    std::multiset<PageLayerPosEntry<Element>> elements{};
    bool eraser = false;
};
