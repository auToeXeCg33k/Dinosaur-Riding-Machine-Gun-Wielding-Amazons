package commands;

import core.World;
import items.Item;

public class PickUp implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 2) {
        if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
            if (world.getItemClassMap().get(strs[1]) != null)
              for (int i = 0; i < (world.getTiles()).length; i++) {
                for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                  if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                    for (int k = 0; k < world.getTiles()[i][j].getItemList().size(); k++) {
                      if (((Item)world.getTiles()[i][j].getItemList().get(k)).getClass().equals(world.getItemClassMap().get(strs[1]))) {
                        if (((Select)world.getCommandMap().get("select")).getSelection().putInInventory(world.getTiles()[i][j].getItemList().get(k))) {
                          world.getTiles()[i][j].rmItem(world.getTiles()[i][j].getItemList().get(k));
                          System.out.println(strs[1] + " felvéve.\n");
                          world.incCounter();
                          return;
                        } 
                        System.out.println("Nem sikerült felvenni.\n");
                        return;
                      } 
                    } 
                    System.out.println(strs[1] + " nincs is a közelben.\n");
                    return;
                  } 
                } 
              }  
            System.out.println("Olyan item, hogy " + strs[1] + " nincs is.\n");
            return;
          } 
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él!\n");
          return;
        } 
        System.out.println("Válasszá ki valakit!\n");
        return;
      } 
      System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
      return;
    } 
    System.out.println("Nincs több lépésed.\n");
  }
}
