public class Move implements Command {
  public void execute(String[] strs, World world) {
    boolean repeat = true;
    if (((Select)world.getCommandMap().get("select")).isSelected())
      if (((Select)world.getCommandMap().get("select")).getSelection() instanceof Amazon) {
        for (int i = 0; i < (world.getTiles()).length && repeat; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length && repeat; j++) {
            if (world.getTiles()[i][j].containsAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection()))
              try {
                int temp1 = Integer.parseInt(strs[1]) - 1;
                int temp2 = Integer.parseInt(strs[2]) - 1;
                if (temp1 >= world.getX() || temp2 >= world.getY()) {
                  System.out.println("ilyen hely nincs is, a faszom se tudja idetenni");
                } else if (temp1 == i && temp2 == j) {
                  System.out.println("mán ott vagy fiam");
                } else {
                  world.getTiles()[i][j].rmAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection());
                  world.getTiles()[temp1][temp2].addAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection());
                  System.out.println(((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " elmozdult a(z) " + ((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + ";" + temp1 + 1 + " koordinátákra.");
                } 
                repeat = false;
              } catch (NumberFormatException ex) {
                System.out.println("ezek nem is számok bazdmeg");
              }  
          } 
        } 
      } else {
        for (int i = 0; i < (world.getTiles()).length && repeat; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length && repeat; j++) {
            if (world.getTiles()[i][j].containsDinoszaurusz((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()))
              try {
                int temp1 = Integer.parseInt(strs[1]) - 1;
                int temp2 = Integer.parseInt(strs[2]) - 1;
                if (temp1 >= world.getX() || temp2 >= world.getY()) {
                  System.out.println("ilyen hely nincs is, a faszom se tudja idetenni");
                } else {
                  world.getTiles()[i][j].rmDinoszaurusz((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection());
                  world.getTiles()[temp1][temp2].addDinoszaurusz((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection());
                  System.out.println(((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " elmozdult a(z) " + ((Dinoszaurusz)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + ";" + temp1 + 1 + " koordinátákra.");
                } 
                repeat = false;
              } catch (NumberFormatException ex) {
                System.out.println("ezek nem is számok bazdmeg");
              }  
          } 
        } 
      }  
  }
  
  public boolean execute() {
    return false;
  }
}
