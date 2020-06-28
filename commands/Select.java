package commands;

import core.Data;
import entities.Amazon;

public class Select implements Command {
  private Amazon selection;
  
  public String execute(String[] strs, Data data) {
    if (strs.length == 2) {
      if (data.getActivePlayer().hasAmazon(strs[1])) {
        this.selection = data.getActivePlayer().getAmazon(strs[1]);
        return strs[1] + " kiválasztva.\n";
      } 
      this.selection = null;
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
