import java.util.Map;

class Attack implements Command {
  private String selection;
  
  public void execute(String param1, Map<String, DinoszauruszonLovagloGepfegyveresAmazon> param2, Select command) {
    if (command.isSelected()) {
      this.selection = command.getSelection();
      ((DinoszauruszonLovagloGepfegyveresAmazon)param2.get(this.selection)).tamad(param2.get(param1));
    } else {
      System.out.println("válasszá valamit buzi");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
