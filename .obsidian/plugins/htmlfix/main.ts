import { Plugin } from "obsidian";

export default class HtmlLocalSrcPlugin extends Plugin {
  async onload() {
    this.registerMarkdownPostProcessor((element) => {

      const targetLinks = Array.from(element.getElementsByTagName("img")).filter(
        (link) =>
          link.src.contains("_media") // Can potentially be removed if image URLs directly reference "Images" folder
      );

      //@ts-ignore
      let base_path = this.app.vault.adapter.basePath;
      console.log('base_path: ' + base_path)
      const active_file_path = this.app.workspace.getActiveFile().path;
      // const active_path = active_file_path.substring(0, active_file_path.lastIndexOf("/")); // Removed
      console.log('active_file_path: ' + active_path)
      for (const link of targetLinks) {
        let clean_link = link.src.replace('app://obsidian.md/', '')
        console.log('clean_link: ' + clean_link)
        let full_link = 'app://local' + base_path + '/' + clean_link; // Modified line (Option 1)
        console.log('full_link: ' + full_link)
        link.src = full_link

        }
    });
  }
}

