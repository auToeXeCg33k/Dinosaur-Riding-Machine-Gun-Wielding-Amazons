package commands;

import core.World;

public class Move implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 3) {
        if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D)
            for (int i = 0; i < (world.getTiles()).length; i++) {
              for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection()))
                  try {
                    int temp1, temp2;
                    if (world.getActivePlayer()) {
                      temp1 = world.getY() - Integer.parseInt(strs[2]);
                      temp2 = world.getX() - Integer.parseInt(strs[1]);
                    } else {
                      temp1 = Integer.parseInt(strs[2]) - 1;
                      temp2 = Integer.parseInt(strs[1]) - 1;
                    } 
                    if (temp1 >= world.getX() || temp2 >= world.getY() || temp1 < 0 || temp2 < 0) {
                      System.out.println("Ilyen hely nincs is, a fasse tudja idetenni!\n");
                      return;
                    } 
                    if (temp1 == i && temp2 == j) {
                      System.out.println("Mán ott vagy, fiam...\n");
                      return;
                    } 
                    if (temp1 > i + 1 || temp1 < i - 1 || temp2 > j + 1 || temp2 < j - 1) {
                      System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " csak környezö koordinátákra mehet!\n");
                      return;
                    } 
                    world.getTiles()[i][j].rmAmazon(((Select)world.getCommandMap().get("select")).getSelection());
                    world.getTiles()[temp1][temp2].addAmazon(((Select)world.getCommandMap().get("select")).getSelection());
                    System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " elmozdult a(z) " + ((Select)world.getCommandMap().get("select")).getSelection().getNev() + ";" + strs[1] + " koordinátákra.\n");
                    world.incCounter();
                    return;
                  } catch (NumberFormatException ex) {
                    System.out.println("Ezek nem is számok bazdmeg...\n");
                    return;
                  }  
              } 
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
