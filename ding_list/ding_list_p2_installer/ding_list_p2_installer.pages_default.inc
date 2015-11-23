<?php

/**
 * @file
 * ding_list_p2_installer.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function ding_list_p2_installer_default_page_manager_pages() {
  $page = new stdClass();
  /* Edit this to true to make a default page disabled initially */

  $page->disabled = FALSE;
  $page->api_version = 1;
  $page->name = 'createtest';
  $page->task = 'page';
  $page->admin_title = 'Create list';
  $page->admin_description = '';
  $page->path = 'user/%user/createlist';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 1,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => TRUE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array(
    'type' => 'action',
    'title' => 'Create list',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'tab',
      'title' => 'asdas',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'user' => array(
      'id' => 1,
      'identifier' => 'Bruger: ID',
      'name' => 'entity_id:user',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_createtest_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'createtest';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-1';
  $pane->panel = 'left_sidebar';
  $pane->type = 'user_menu';
  $pane->subtype = 'user_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'path' => '',
    'context' => 'argument_entity_id:user_1',
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-1'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-1';
  $pane = new stdClass();
  $pane->pid = 'new-2';
  $pane->panel = 'main_content';
  $pane->type = 'list_create';
  $pane->subtype = 'list_create';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-2'] = $pane;
  $display->panels['main_content'][0] = 'new-2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-2';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['createtest'] = $page;

  $page = new stdClass();
  /* Edit this to true to make a default page disabled initially */

  $page->disabled = FALSE;
  $page->api_version = 1;
  $page->name = 'page_ding_list_edit';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List Edit';
  $page->admin_description = '';
  $page->path = 'list/%ding_type/edit';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'edit',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:ding_type_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_edit_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_edit';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'user_list',
          'settings' => array(
            'visibility_settings' => 'edit',
          ),
          'context' => array(
            0 => 'logged-in-user',
            1 => 'argument_entity_id:ding_type_1',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%ding_type:title';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-3';
  $pane->panel = 'left_sidebar';
  $pane->type = 'list_menu';
  $pane->subtype = 'list_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-3'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-3';
  $pane = new stdClass();
  $pane->pid = 'new-4';
  $pane->panel = 'main_content';
  $pane->type = 'edit_list';
  $pane->subtype = 'edit_list';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-4'] = $pane;
  $display->panels['main_content'][0] = 'new-4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_edit'] = $page;

  $page = new stdClass();
  /* Edit this to true to make a default page disabled initially */

  $page->disabled = FALSE;
  $page->api_version = 1;
  $page->name = 'page_ding_list_share';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List Share';
  $page->admin_description = '';
  $page->path = 'list/%ding_type/share';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'owner',
        ),
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:ding_type_1',
        ),
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_share_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_share';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'user_list',
          'settings' => array(
            'visibility_settings' => 'edit',
          ),
          'context' => array(
            0 => 'logged-in-user',
            1 => 'argument_entity_id:ding_type_1',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%ding_type:title';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-5';
  $pane->panel = 'left_sidebar';
  $pane->type = 'list_menu';
  $pane->subtype = 'list_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-5'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-5';
  $pane = new stdClass();
  $pane->pid = 'new-6';
  $pane->panel = 'main_content';
  $pane->type = 'share_list';
  $pane->subtype = 'share_list';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-6'] = $pane;
  $display->panels['main_content'][0] = 'new-6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_share'] = $page;

  $page = new stdClass();
  /* Edit this to true to make a default page disabled initially */

  $page->disabled = FALSE;
  $page->api_version = 1;
  $page->name = 'page_ding_list_view';
  $page->task = 'page';
  $page->admin_title = 'Page Ding List View';
  $page->admin_description = '';
  $page->path = 'list/%ding_type';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'user_list',
        'settings' => array(
          'visibility_settings' => 'view',
          'list_argument' => '2',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array(
    'ding_type' => array(
      'id' => 1,
      'identifier' => 'ding_type: ID',
      'name' => 'entity_id:ding_type',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_view_panel_context_2';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'Interest list panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:ding_type:ding_list:field_list_type',
          'settings' => array(
            'field_list_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'interests',
                ),
              ),
            ),
            'field_list_type_value' => array(
              0 => array(
                'value' => 'interests',
              ),
            ),
            'field_list_type_format' => array(
              0 => array(
                'value' => 'interests',
              ),
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'bottom' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%ding_type:title';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-7';
  $pane->panel = 'left_sidebar';
  $pane->type = 'list_menu';
  $pane->subtype = 'list_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-7'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-7';
  $pane = new stdClass();
  $pane->pid = 'new-8';
  $pane->panel = 'main_content';
  $pane->type = 'list_followers';
  $pane->subtype = 'list_followers';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-8'] = $pane;
  $display->panels['main_content'][0] = 'new-8';
  $pane = new stdClass();
  $pane->pid = 'new-9';
  $pane->panel = 'main_content';
  $pane->type = 'views_panes';
  $pane->subtype = 'ding_list_elements-panel_pane_2';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 0,
    'pager_id' => '0',
    'items_per_page' => '10',
    'offset' => '0',
    'override_title' => 1,
    'override_title_text' => '<none>',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $display->content['new-9'] = $pane;
  $display->panels['main_content'][1] = 'new-9';
  $pane = new stdClass();
  $pane->pid = 'new-10';
  $pane->panel = 'main_content';
  $pane->type = 'add_list';
  $pane->subtype = 'add_list';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $display->content['new-10'] = $pane;
  $display->panels['main_content'][2] = 'new-10';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-8';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_view_panel_context_3';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -29;
  $handler->conf = array(
    'title' => 'Ratings list panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_field_value:ding_type:ding_list:field_list_type',
          'settings' => array(
            'field_list_type' => array(
              'und' => array(
                0 => array(
                  'value' => 'ratings',
                ),
              ),
            ),
            'field_list_type_value' => array(
              0 => array(
                'value' => 'ratings',
              ),
            ),
            'field_list_type_format' => array(
              0 => array(
                'value' => 'ratings',
              ),
            ),
          ),
          'context' => 'argument_entity_id:ding_type_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'branding' => NULL,
      'header' => NULL,
      'navigation' => NULL,
      'content' => NULL,
      'footer' => NULL,
      'bottom' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-11';
  $pane->panel = 'left_sidebar';
  $pane->type = 'list_menu';
  $pane->subtype = 'list_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-11'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-11';
  $pane = new stdClass();
  $pane->pid = 'new-12';
  $pane->panel = 'main_content';
  $pane->type = 'list_followers';
  $pane->subtype = 'list_followers';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-12'] = $pane;
  $display->panels['main_content'][0] = 'new-12';
  $pane = new stdClass();
  $pane->pid = 'new-13';
  $pane->panel = 'main_content';
  $pane->type = 'views_panes';
  $pane->subtype = 'ding_list_elements-panel_pane_3';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 0,
    'pager_id' => '0',
    'items_per_page' => '10',
    'offset' => '0',
    'override_title' => 1,
    'override_title_text' => '<none>',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $display->content['new-13'] = $pane;
  $display->panels['main_content'][1] = 'new-13';
  $pane = new stdClass();
  $pane->pid = 'new-14';
  $pane->panel = 'main_content';
  $pane->type = 'add_list';
  $pane->subtype = 'add_list';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $display->content['new-14'] = $pane;
  $display->panels['main_content'][2] = 'new-14';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-12';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $handler = new stdClass();
  /* Edit this to true to make a default handler disabled initially */

  $handler->disabled = FALSE;
  $handler->api_version = 1;
  $handler->name = 'page_page_ding_list_view_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_ding_list_view';
  $handler->handler = 'panel_context';
  $handler->weight = -28;
  $handler->conf = array(
    'title' => 'Default panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = '25_50_25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left_sidebar' => NULL,
      'main_content' => NULL,
      'right_sidebar' => NULL,
      'attachment_4_1' => NULL,
      'attachment_4_2' => NULL,
      'attachment_4_3' => NULL,
      'attachment_4_4' => NULL,
      'attachment_3_1' => NULL,
      'attachment_3_2' => NULL,
      'attachment_3_3' => NULL,
      'attachment_2_1' => NULL,
      'attachment_2_2' => NULL,
      'attachment_1_1' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%ding_type:title';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-15';
  $pane->panel = 'left_sidebar';
  $pane->type = 'list_menu';
  $pane->subtype = 'list_menu';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-15'] = $pane;
  $display->panels['left_sidebar'][0] = 'new-15';
  $pane = new stdClass();
  $pane->pid = 'new-16';
  $pane->panel = 'main_content';
  $pane->type = 'list_followers';
  $pane->subtype = 'list_followers';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $display->content['new-16'] = $pane;
  $display->panels['main_content'][0] = 'new-16';
  $pane = new stdClass();
  $pane->pid = 'new-17';
  $pane->panel = 'main_content';
  $pane->type = 'views_panes';
  $pane->subtype = 'ding_list_elements-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'use_pager' => 0,
    'pager_id' => '0',
    'items_per_page' => '10',
    'offset' => '0',
    'override_title' => 1,
    'override_title_text' => '<none>',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $display->content['new-17'] = $pane;
  $display->panels['main_content'][1] = 'new-17';
  $pane = new stdClass();
  $pane->pid = 'new-18';
  $pane->panel = 'main_content';
  $pane->type = 'list_view';
  $pane->subtype = 'list_view';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $display->content['new-18'] = $pane;
  $display->panels['main_content'][2] = 'new-18';
  $pane = new stdClass();
  $pane->pid = 'new-19';
  $pane->panel = 'main_content';
  $pane->type = 'add_list';
  $pane->subtype = 'add_list';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $display->content['new-19'] = $pane;
  $display->panels['main_content'][3] = 'new-19';
  $pane = new stdClass();
  $pane->pid = 'new-20';
  $pane->panel = 'main_content';
  $pane->type = 'sharer_pane';
  $pane->subtype = 'sharer_pane';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'count' => '5',
    'override_title' => 0,
    'override_title_text' => '',
    'communities' => array(
      'facebook' => 'facebook',
      'twitter' => 'twitter',
    ),
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $display->content['new-20'] = $pane;
  $display->panels['main_content'][4] = 'new-20';
  $display->hide_title = PANELS_TITLE_PANE;
  $display->title_pane = 'new-16';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_ding_list_view'] = $page;

  return $pages;
}
