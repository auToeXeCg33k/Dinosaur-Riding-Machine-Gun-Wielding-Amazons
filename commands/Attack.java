package commands;

import core.Data;
import units.*;


public class Attack implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        if (data.getMaxMoves() == data.getMoves())
            return new Report("Nincs több lépésed.\n", false);

        if (strs.length != 2)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection() == null)
            return new Report("Válasszá valami buzit!\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getHP() == 0.0)
            return new Report (((Select) data.getCommands().get("select")).getSelection().getNev() + " nem is él.\n", false);

        if (((Select) data.getCommands().get("select")).getSelection().getGepFegyver() == null)
            return new Report ("Nem tok durrogtatni, fasse fogok.\n", false);

        if (!data.getPlayers().get(!data.getPlayerMarker()).hasAmazon(strs[1]))
            return new Report (strs[1] + " nem is létezik.\n", false);

        Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
        if (!data.getWorld().getTiles()[p.getY()][p.getX()].contains(data.getPlayers().get(!data.getPlayerMarker()).getAmazon(strs[1])))
            return new Report (strs[1] + " nincs is rangeben.\n", false);

        if (data.getPlayers().get(!data.getPlayerMarker()).getAmazon(strs[1]).getHP() == 0.0)
            return new Report(strs[1] + " is nem él.\n", false);

        String ret = ((Select) data.getCommands().get("select")).getSelection().tamad(data.getPlayers().get(!data.getPlayerMarker()).getAmazon(strs[1])) + data.nextMove();
        if (data.getPlayers().get(!data.getPlayerMarker()).getAmazon(strs[1]).getHP() == 0.0)
            data.getPlayers().get(!data.getPlayerMarker()).decActive();
        return new Report(ret, false);
    }
}