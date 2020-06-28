package commands;

import core.Data;
import core.Player;
import units.Report;

public class New implements Command {
  public Report execute(String[] strs, Data data) {
    if (data.getMaxMoves() == data.getMoves())
      return new Report("Nincs több lépésed.\n", false); 
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).hasAmazon(strs[1]))
      return new Report(strs[1] + " már létezik.\n", false); 
    if (((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getSpawns() == data.getMaxSpawn() || ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getActives() == data.getMaxActive())
      return new Report("Elfogyott a spawn more!\n", false); 
    String ret = data.newAmazon(strs[1]);
    ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).incSpawn();
    ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).incActive();
    return new Report(ret.concat(data.nextMove()), false);
  }
}
