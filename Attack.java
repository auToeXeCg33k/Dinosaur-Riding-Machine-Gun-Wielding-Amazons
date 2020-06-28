class Attack implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).isSelected()) {
        if (((Select)world.getCommandMap().get("select")).getSelection() instanceof Amazon) {
          if (world.getAmazonMap().containsKey(strs[1])) {
            ((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).tamad(world.getAmazonMap().get(strs[1]));
          } else {
            System.out.println("ilyen amazon nincs - currently csak amazonokat lehet támadni");
          } 
        } else if (((Select)world.getCommandMap().get("select")).getSelection() instanceof Dinoszaurusz) {
          System.out.println("a dínók egyenlőre nem tudnak támadni");
        } 
      } else {
        System.out.println("válasszá valami buzit");
      } 
    } else if (strs.length > 2) {
      System.out.println("túl sok argumentum");
    } else {
      System.out.println("túl kevés argumentum");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
