package commands;

import core.World;
import items.Item;

public class Drop implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 2) {
        if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
            if (world.getItemClassMap().get(strs[1]) != null)
              for (int i = 0; i < (world.getTiles()).length; i++) {
                for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                  if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                    Item temp = ((Select)world.getCommandMap().get("select")).getSelection().dropFromInventory((Class)world.getItemClassMap().get(strs[1]));
                    if (temp != null) {
                      world.getTiles()[i][j].addItem(temp);
                      System.out.println(strs[1] + "eldobva.\n");
                      world.incCounter();
                      return;
                    } 
                    System.out.println("Nem sikerült eldobni.\n");
                    return;
                  } 
                } 
              }  
            System.out.println("Olyen item, hogy " + strs[1] + ", nincs is!\n");
            return;
          } 
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él.\n");
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
