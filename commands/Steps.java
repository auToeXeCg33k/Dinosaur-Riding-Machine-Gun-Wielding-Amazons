package commands;

import core.Data;

public class Steps implements Command {
  public String execute(String[] strs, Data data) {
    return "A hátralévő lépéseid száma: " + data.getCounters().getMaxMoves() - data.getCounters().getMoves() + ".\nA összes spawnod száma: " + data
      .getActivePlayer().getSpawns() + ".\nAz éppen élő amazonjaid száma: " + data
      .getActivePlayer().getActives() + ".\nA aktuális spawnlehetőségeid száma: " + 
      
      Math.min(data.getCounters().getMaxActive() - data.getActivePlayer().getActives(), data.getCounters().getMaxSpawn() - data.getActivePlayer().getSpawns()) + ".\n";
  }
}
