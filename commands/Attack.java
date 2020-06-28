package commands;

import core.Player;
import core.World;
import entities.Amazon;

public class Attack implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 2) {
        if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getHP() != 0.0D) {
            if (((Player)world.getPlayerMap().get(Boolean.valueOf(!world.getActivePlayer()))).getAmazonMap().containsKey(strs[1]))
              for (int i = 0; i < (world.getTiles()).length; i++) {
                for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                  if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                    if (world.getTiles()[i][j].containsAmazon((Amazon)((Player)world.getPlayerMap().get(Boolean.valueOf(!world.getActivePlayer()))).getAmazonMap().get(strs[1]))) {
                      if (((Amazon)((Player)world.getPlayerMap().get(Boolean.valueOf(!world.getActivePlayer()))).getAmazonMap().get(strs[1])).getHP() != 0.0D) {
                        switch (((Select)world.getCommandMap().get("select")).getSelection().tamad((Amazon)((Player)world.getPlayerMap().get(Boolean.valueOf(!world.getActivePlayer()))).getAmazonMap().get(strs[1]))) {
                          case 0:
                            world.incCounter();
                            return;
                          case 1:
                            ((Player)world.getPlayerMap().get(Boolean.valueOf(!world.getActivePlayer()))).decActive();
                            world.incCounter();
                            return;
                        } 
                        return;
                      } 
                      System.out.println(strs[1] + " is nem él.\n");
                      return;
                    } 
                    System.out.println(strs[1] + " nincs is rangeben.\n");
                    return;
                  } 
                } 
              }  
            System.out.println(strs[1] + " nem is létezik.\n");
            return;
          } 
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él.\n");
          return;
        } 
        System.out.println("Válasszá valami buzit!\n");
        return;
      } 
      System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
      return;
    } 
    System.out.println("Nincs több lépésed.\n");
  }
}
