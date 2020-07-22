package commands;

import core.Data;
import units.*;

public class GetOff implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        if (strs.length != 1)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection() == null)
            return new Report("Válasszá ki valakit!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getHP() == 0.0)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz() == null)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " amazonnak nincs dinója. Idomíts be vele egyet!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz().getHP() == 0.0)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " dinoszaurusza nem él. Hullákról már nem nagyon lehet hogy leszállni dik...\n", false);

        if (!((Select) data.getCommands().get("select")).getSelection().isLovagol())
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " nem is lovagol!\n", false);

        Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
        data.getWorld().getTiles()[p.getY()][p.getX()].add(((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz());
        ((Select) data.getCommands().get("select")).getSelection().setLovagol(false);
        return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " leszállt a dinoszauruszról.\n", false);
    }
}