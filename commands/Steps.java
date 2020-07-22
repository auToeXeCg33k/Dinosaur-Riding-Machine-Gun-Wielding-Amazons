package commands;

import core.Data;
import units.Report;

public class Steps implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        return new Report("A hátralévő lépéseid száma: " + (data.getMaxMoves() - data.getMoves()) + ".\n" +
                "A összes spawnod száma: " + data.getPlayers().get(data.getPlayerMarker()).getSpawns() + ".\n" +
                "Az éppen élő amazonjaid száma: " + data.getPlayers().get(data.getPlayerMarker()).getActives() + ".\n" +
                "A aktuális spawnlehetőségeid száma: " +
                Math.min((data.getMaxActive() - data.getPlayers().get(data.getPlayerMarker()).getActives()), data.getMaxSpawn() - data.getPlayers().get(data.getPlayerMarker()).getSpawns()) + ".\n", false);

    }
}