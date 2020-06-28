package commands;

import core.Data;
import core.Player;
import entities.Amazon;

public class Select implements Command {
  private Amazon selection;
  
  public String execute(String[] strs, Data data) {
    if (strs.length == 2) {
      if (((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).hasAmazon(strs[1])) {
        if (this.selection == ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getAmazon(strs[1]))
          return strs[1] + " már ki van választva.\n"; 
        this.selection = ((Player)data.getPlayers().get(Boolean.valueOf(data.getPlayerMarker()))).getAmazon(strs[1]);
        return strs[1] + " kiválasztva.\n";
      } 
      return strs[1] + " nem is van!\n";
    } 
    return "Nem megfelelő a gyökérségek száma heló!\n";
  }
  
  public Amazon getSelection() {
    return this.selection;
  }
  
  public void clearSelection() {
    this.selection = null;
  }
}
