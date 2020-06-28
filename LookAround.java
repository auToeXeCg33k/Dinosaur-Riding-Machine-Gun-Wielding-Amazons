public class LookAround implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        for (int i = 0; i < (world.getTiles()).length; i++) {
          for (int j = 0; j < (world.getTiles()[0]).length; j++) {
            if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
              System.out.print("Amazonok az aktuális koordinátán: ");
              for (Amazon amazon : world.getTiles()[i][j].getAmazonSet()) {
                if (amazon != ((Select)world.getCommandMap().get("select")).getSelection())
                  System.out.print(amazon.getNev() + " "); 
              } 
              System.out.print("\nDinoszauruszok az aktuális koordinátán: ");
              for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j].getDinoszauruszSet())
                System.out.print(dinoszaurusz.getNev() + " "); 
              try {
                if (world.getTiles()[i + 1][j].exists()) {
                  System.out.print("\nAmazonok északra: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok északra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j + 1].exists()) {
                  System.out.print("\nAmazonok az észak-keletre: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok észak-keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j + 1].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j + 1].exists()) {
                  System.out.print("\nAmazonok keletre: ");
                  for (Amazon amazon : world.getTiles()[i][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j + 1].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j + 1].exists()) {
                  System.out.print("\nAmazonok dél-keletre: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.println("\nDinoszauruszok dél-keletre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j + 1].getDinoszauruszSet())
                    System.out.println(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j].exists()) {
                  System.out.print("\nAmazonok délre: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok délre: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i - 1][j - 1].exists()) {
                  System.out.print("\nAmazonok dél-nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i - 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok dél-nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j - 1].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i][j - 1].exists()) {
                  System.out.print("\nAmazonok nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j - 1].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              try {
                if (world.getTiles()[i + 1][j - 1].exists()) {
                  System.out.print("\nAmazonok észak-nyugatra: ");
                  for (Amazon amazon : world.getTiles()[i + 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + " "); 
                  System.out.print("\nDinoszauruszok észak-nyugatra: ");
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j - 1].getDinoszauruszSet())
                    System.out.print(dinoszaurusz.getNev() + " "); 
                } 
              } catch (ArrayIndexOutOfBoundsException arrayIndexOutOfBoundsException) {}
              System.out.println();
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
