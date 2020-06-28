package core;

import java.util.Map;

public class Tracker {
  public String track(Data data) {
    for (Map.Entry<Boolean, Player> entry : data.getPlayers().entrySet()) {
      if (((Player)entry.getValue()).getSpawns() == data.getMaxSpawn() && ((Player)entry.getValue()).getActives() == 0)
        return "\n---A játéknak vége! A nyertes: Player " + (((Boolean)entry.getKey()).booleanValue() ? "1" : "2") + "! GG---\nA kilépéshez nyomj entert!\n"; 
    } 
    return null;
  }
}
