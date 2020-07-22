package commands;

import core.Data;
import units.Report;
import entities.Amazon;

public class Select implements Command {
    private Amazon selection;


    @Override
    public Report execute(String[] strs, Data data) {
        if (strs.length != 2)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (!data.getPlayers().get(data.getPlayerMarker()).hasAmazon(strs[1]))
            return new Report(strs[1] + " nem is van!\n", false);

        if (selection == data.getPlayers().get(data.getPlayerMarker()).getAmazon(strs[1]))
            return new Report(strs[1] + " már ki van választva.\n", false);

        selection = data.getPlayers().get(data.getPlayerMarker()).getAmazon(strs[1]);
        return new Report(strs[1] + " kiválasztva.\n", false);
    }


    public Amazon getSelection() {
        return selection;
    }
    public void clearSelection() {
        this.selection = null;
    }
}