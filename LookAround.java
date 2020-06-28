public class LookAround implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).isSelected()) {
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon((Amazon)((Select)world.getCommandMap().get("select")).getSelection())) {
              System.out.println("Amazonok az aktuális koordinátán:");
              for (Amazon amazon : world.getTiles()[i][j].getAmazonSet()) {
                if (amazon != ((Select)world.getCommandMap().get("select")).getSelection())
                  System.out.println(amazon.toString()); 
              } 
              System.out.println("Dinoszauruszok az aktuális koordinátán:");
              for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j].getDinoszauruszSet())
                System.out.println(dinoszaurusz.toString()); 
              try {
                if (world.getTiles()[i + 1][j].exists()) {
                  System.out.println("Amazonok északra:");
                  for (Amazon amazon : world.getTiles()[i + 1][j].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok északra:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j + 1].exists()) {
                  System.out.println("Amazonok az észak-keletre:");
                  for (Amazon amazon : world.getTiles()[i + 1][j + 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok észak-keletre:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j + 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j + 1].exists()) {
                  System.out.println("Amazonok keletre:");
                  for (Amazon amazon : world.getTiles()[i][j + 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok keletre:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j + 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j + 1].exists()) {
                  System.out.println("Amazonok dél-keletre:");
                  for (Amazon amazon : world.getTiles()[i - 1][j + 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok dél-keletre:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j + 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j].exists()) {
                  System.out.println("Amazonok délre:");
                  for (Amazon amazon : world.getTiles()[i - 1][j].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok délre");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j - 1].exists()) {
                  System.out.println("Amazonok dél-nyugatra:");
                  for (Amazon amazon : world.getTiles()[i - 1][j - 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok dél-nyugatra:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j - 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j - 1].exists()) {
                  System.out.println("Amazonok nyugatra:");
                  for (Amazon amazon : world.getTiles()[i][j - 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok nyugatra:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j - 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j - 1].exists()) {
                  System.out.println("Amazonok észak-nyugatra:");
                  for (Amazon amazon : world.getTiles()[i + 1][j - 1].getAmazonSet())
                    System.out.println(amazon.toString()); 
                  System.out.println("Dinoszauruszok észak-nyugatra:");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j - 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.toString()); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
            } 
          } 
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
