package commands;

import core.Data;
import units.*;

public class GetOn implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        if (strs.length != 1)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection() == null)
            return new Report("Válasszá valakit!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getHP() == 0.0)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz() == null)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " amazonnak nincs dinója. Idomíts be vele egyet!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().isLovagol())
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " már lovagol!\n", false);

        Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
        if (!data.getWorld().getTiles()[p.getY()][p.getX()].contains(((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz()))
            return new Report("Nincs itt a dinó.\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz().getHP() == 0.0)
            return new Report("A dinó ki van múlva.\n", false);

        data.getWorld().getTiles()[p.getY()][p.getX()].remove(((Select) data.getCommands().get("select")).getSelection().getDinoszaurusz());
        ((Select) data.getCommands().get("select")).getSelection().setLovagol(true);
        return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " felszállt a dinoszauruszra.\n", false);
    }
}