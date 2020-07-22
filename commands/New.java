package commands;

import core.Data;
import units.Report;


public class New implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        if (data.getMaxMoves() == data.getMoves())
            return new Report("Nincs több lépésed.\n", false);

        if (strs.length != 2)
            return new Report("Nem megfelelő a gyökérségek száma heló!\n", false);

        if (data.getPlayers().get(data.getPlayerMarker()).hasAmazon(strs[1]))
            return new Report(strs[1] + " már létezik.\n", false);

        if (data.getPlayers().get(data.getPlayerMarker()).getSpawns() == data.getMaxSpawn() || data.getPlayers().get(data.getPlayerMarker()).getActives() == data.getMaxActive())
            return new Report("Elfogyott a spawn more!\n", false);

        String ret = data.newAmazon(strs[1]);
        data.getPlayers().get(data.getPlayerMarker()).incSpawn();
        data.getPlayers().get(data.getPlayerMarker()).incActive();
        return new Report(ret.concat(data.nextMove()), false);
    }
}