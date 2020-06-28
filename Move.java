public class Move implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 3) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D)
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection()))
                try {
                  int temp1 = Integer.parseInt(strs[1]) - 1;
                  int temp2 = Integer.parseInt(strs[2]) - 1;
                  if (temp1 >= world.getX() || temp2 >= world.getY()) {
                    System.out.println("ilyen hely nincs is, a faszom se tudja idetenni");
                    return;
                  } 
                  if (temp1 == i && temp2 == j) {
                    System.out.println("mán ott vagy fiam");
                    return;
                  } 
                  if (((Select)world.getCommandMap().get("select")).getSelection().isLovagol()) {
                    world.getTiles()[i][j].rmDinoszaurusz(((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz());
                    world.getTiles()[temp1][temp2].addDinoszaurusz(((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz());
                  } 
                  world.getTiles()[i][j].rmAmazon(((Select)world.getCommandMap().get("select")).getSelection());
                  world.getTiles()[temp1][temp2].addAmazon(((Select)world.getCommandMap().get("select")).getSelection());
                  System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " elmozdult a(z) " + ((Select)world.getCommandMap().get("select")).getSelection().getNev() + ";" + temp1 + 1 + " koordinátákra.");
                  return;
                } catch (NumberFormatException ex) {
                  System.out.println("ezek nem is számok bazdmeg");
                  return;
                }  
            } 
          }  
        System.out.println("A kiválasztott amazon nem is él");
        return;
      } 
      System.out.println("válasszá valakit először");
      return;
    } 
    System.out.println("nem megfelelő argumentummennyiség");
  }
  
  public boolean execute() {
    return false;
  }
}
