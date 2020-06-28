package core;

import java.util.Map;

public class Tracker {
  public Report track(Data data) {
    for (Map.Entry<Boolean, Player> entry : data.getPlayers().entrySet()) {
      if (((Player)entry.getValue()).getSpawns() == data.getMaxSpawn() && ((Player)entry.getValue()).getActives() == 0)
        return new Report("\n---A játéknak vége! A nyertes: Player " + (((Boolean)entry.getKey()).booleanValue() ? "1" : "2") + "! GG---\nA kilépéshez nyomj entert!\n", true); 
    } 
    return new Report("", false);
  }
}
