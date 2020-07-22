package core;

import java.util.HashMap;

public class Tracker {
    public String track(Data data) {
        for (HashMap.Entry<Boolean, Player> entry : data.getPlayers().entrySet()) {
            if (entry.getValue().getSpawns() == data.getMaxSpawn() && entry.getValue().getActives() == 0) {
                return "\n---A játéknak vége! A nyertes: Player " + (entry.getKey()? "1" : "2") + "! GG---\n" +
                "A kilépéshez nyomj entert!\n";
            }
        }
        return null;
    }
}