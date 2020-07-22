package commands;

import core.Data;
import units.Report;
import entities.Amazon;
import java.util.HashMap;

public class List implements Command {

    @Override
    public Report execute(String[] strs, Data data) {
        String string = "";
        for (HashMap.Entry<String, Amazon> entry : data.getPlayers().get(data.getPlayerMarker()).getAmazonMap().entrySet()) {
            string = string.concat(entry.getKey() + ", ");
        }
        if (string.equals("")) {
            return new Report("Nincsenek amazonjaid.\n", false);

        }
        return new Report("Az amazonjaid: " + string.substring(0, string.length()-2) + ".\n", false);
    }
}