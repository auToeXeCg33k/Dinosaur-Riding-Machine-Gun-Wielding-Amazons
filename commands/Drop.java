package commands;

import core.Data;
import units.*;
import items.Item;

public class Drop implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        if (data.getMaxMoves() == data.getMoves())
            return new Report("Nincs több lépésed.\n", false);

        if (strs.length != 2)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection() == null)
            return new Report("Válasszá ki valakit!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getHP() == 0.0)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n", false);

        if (data.getItems().get(strs[1]) == null)
            return new Report("Olyen item, hogy " + strs[1] + ", nincs is!\n", false);

        Item dropped = ((Select) data.getCommands().get("select")).getSelection().dropFromInventory(data.getItems().get(strs[1]));
        if (dropped == null)
            return new Report(((Select) data.getCommands().get("select")).getSelection().getNev() + " amazonnál nincs " + strs[1] + ".", false);

        Point p = data.location((((Select)data.getCommands().get("select")).getSelection()));
        data.getWorld().getTiles()[p.getY()][p.getX()].add(dropped);
        return new Report(strs[1] + "eldobva.\n" + data.nextMove(), false);
    }
}