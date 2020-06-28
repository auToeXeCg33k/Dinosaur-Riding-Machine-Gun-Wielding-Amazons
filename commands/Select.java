package commands;

import core.Player;
import core.World;
import entities.Amazon;

public class Select implements Command {
  private Amazon selection;
  
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getAmazonMap().containsKey(strs[1])) {
        this.selection = (Amazon)((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).getAmazonMap().get(strs[1]);
        System.out.println(strs[1] + " kiválasztva.\n");
        return;
      } 
      this.selection = null;
      System.out.println(strs[1] + " nem is van!\n");
      return;
    } 
    System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
  }
  
  public Amazon getSelection() {
    return this.selection;
  }
  
  public void clearSelection() {
    this.selection = null;
  }
}
