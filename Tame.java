import java.util.Scanner;

public class Tame implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() == null)
            for (int i = 0; i < (world.getTiles()).length; i++) {
              for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                  switch (world.getTiles()[i][j].getDinoszauruszList().size()) {
                    case 0:
                      System.out.println("nincs dínó a közelben");
                      return;
                    case 1:
                      if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getTamed()) {
                        System.out.println("Ez a dínó mán másé");
                        return;
                      } 
                      ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(0));
                      System.out.println("Dínó beidomítva");
                      return;
                  } 
                  for (int k = 0; k < world.getTiles()[i][j].getDinoszauruszList().size(); k++)
                    System.out.println("" + k + 1 + ": " + k + 1); 
                  System.out.print("az idomítani kívánt dinoszaurusz száma:");
                  Scanner sc = new Scanner(System.in);
                  String input = sc.nextLine();
                  String[] strings = input.split(" ");
                  if (strings.length == 1)
                    try {
                      int index = Integer.parseInt(strings[0]) - 1;
                      if (index < world.getTiles()[i][j].getDinoszauruszList().size() && index >= 0) {
                        if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getTamed()) {
                          System.out.println("Ez a dínó mán másé");
                          return;
                        } 
                        ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(index));
                        System.out.println("Dínó beidomítva");
                        return;
                      } 
                      System.out.println("mi ez a szám more");
                      return;
                    } catch (NumberFormatException e) {
                      System.out.println("ez nem szám");
                      return;
                    }  
                  System.out.println("túl sok faszság");
                  return;
                } 
              } 
            }  
          System.out.println("az amazonnak mán van dínója");
          return;
        } 
        System.out.println("Ez az amazon nem is él.");
        return;
      } 
      System.out.println("válasszá ki valakit");
      return;
    } 
    System.out.println("nem megfelelő argumentumszám");
  }
  
  public boolean execute() {
    return false;
  }
}
