import java.util.Scanner;

public class Tame implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() == null) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                int k;
                Scanner sc;
                String input;
                String[] strings;
                switch (world.getTiles()[i][j].getDinoszauruszList().size()) {
                  case 0:
                    System.out.println("nincs dínó a közelben");
                    break;
                  case 1:
                    ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(0));
                    break;
                  default:
                    for (k = 0; k < world.getTiles()[i][j].getDinoszauruszList().size(); k++)
                      System.out.println("" + k + 1 + ": " + k + 1); 
                    System.out.print("az idomítani kívánt dinoszaurusz száma:");
                    sc = new Scanner(System.in);
                    input = sc.nextLine();
                    strings = input.split(" ");
                    if (strings.length == 1) {
                      try {
                        int index = Integer.parseInt(strings[0]) - 1;
                        if (index < world.getTiles()[i][j].getDinoszauruszList().size()) {
                          ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(index));
                          break;
                        } 
                        System.out.println("túl nagy szám");
                      } catch (NumberFormatException e) {
                        System.out.println("ez nem szám");
                      } 
                      break;
                    } 
                    System.out.println("túl sok faszság");
                    break;
                } 
              } 
            } 
          } 
        } else {
          System.out.println("az amazonnak mán van dínója");
        } 
      } else {
        System.out.println("válasszá ki valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentumszám");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
