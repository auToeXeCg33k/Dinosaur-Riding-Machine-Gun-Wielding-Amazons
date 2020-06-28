package commands;

import core.Data;
import core.Player;

public class Steps implements Command {
  public String execute(String[] strs, Data data) {
    return "A hátralévő lépéseid száma: " + data.getMaxMoves() - data.getMoves() + ".\nA összes spawnod száma: " + ((Player)data
      .getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getSpawns() + ".\nAz éppen élő amazonjaid száma: " + ((Player)data
      .getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getActives() + ".\nA aktuális spawnlehetőségeid száma: " + 
      
      Math.min(data.getMaxActive() - ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getActives(), data.getMaxSpawn() - ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getSpawns()) + ".\n";
  }
}
