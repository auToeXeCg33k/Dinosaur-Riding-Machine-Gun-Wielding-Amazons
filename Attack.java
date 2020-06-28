class Attack implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (world.getAmazonMap().containsKey(strs[1])) {
          ((Select)world.getCommandMap().get("select")).getSelection().tamad(world.getAmazonMap().get(strs[1]));
        } else {
          System.out.println("ilyen amazon nincs");
        } 
      } else {
        System.out.println("válasszá valami buzit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
