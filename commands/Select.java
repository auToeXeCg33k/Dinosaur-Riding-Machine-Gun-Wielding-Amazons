package commands;

import core.Data;
import core.Player;
import core.Report;
import entities.Amazon;

public class Select implements Command {
  private Amazon selection;
  
  public Report execute(String[] strs, Data data) {
    if (strs.length != 2)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (!((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).hasAmazon(strs[1]))
      return new Report(strs[1] + " nem is van!\n", false); 
    if (this.selection == ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getAmazon(strs[1]))
      return new Report(strs[1] + " már ki van választva.\n", false); 
    this.selection = ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getAmazon(strs[1]);
    return new Report(strs[1] + " kiválasztva.\n", false);
  }
  
  public Amazon getSelection() {
    return this.selection;
  }
  
  public void clearSelection() {
    this.selection = null;
  }
}
