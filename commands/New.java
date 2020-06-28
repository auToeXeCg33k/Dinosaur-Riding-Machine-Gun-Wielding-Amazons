package commands;

import core.Data;
import core.Player;

public class New implements Command {
  public String execute(String[] strs, Data data) {
    if (data.canDoAction()) {
      if (strs.length == 2) {
        if (((Player)data.getMaps().getPlayerMap().get(Boolean.valueOf(data.getPlayerMarker()))).hasAmazon(strs[1]))
          return strs[1] + " már létezik.\n"; 
        if (((Player)data.getMaps().getPlayerMap().get(Boolean.valueOf(data.getPlayerMarker()))).getSpawns() < data.getCounters().getMaxSpawn() && ((Player)data.getMaps().getPlayerMap().get(Boolean.valueOf(data.getPlayerMarker()))).getActives() < data.getCounters().getMaxActive()) {
          String ret = data.newAmazon(strs[1]);
          data.incSpawn();
          data.incActive();
          return ret.concat(data.nextMove());
        } 
        return "Elfogyott a spawn more!\n";
      } 
      return "Nem megfelelő a gyökérségek száma heló!\n";
    } 
    return "Nincs több lépésed.\n";
  }
}
