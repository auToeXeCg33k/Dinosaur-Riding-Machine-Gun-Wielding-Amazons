package commands;

import core.World;

public class Equip implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (world.getItemClassMap().get(strs[1]) != null) {
            if (((Select)world.getCommandMap().get("select")).getSelection().equip((Class)world.getItemClassMap().get(strs[1]))) {
              System.out.println(strs[1] + " kézbe véve.\n");
              return;
            } 
            System.out.println("Nincs is " + strs[1] + " az inventoryban!\n");
            return;
          } 
          System.out.println("Olyan fegyver, hogy " + strs[1] + ", nincs is!\n");
          return;
        } 
        System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él!\n");
        return;
      } 
      System.out.println("Válasszá ki valakit!\n");
      return;
    } 
    System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
  }
}
