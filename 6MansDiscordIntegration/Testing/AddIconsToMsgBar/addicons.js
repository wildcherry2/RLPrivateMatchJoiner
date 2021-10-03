//create plugins folder in bdbuild to compile, soft link this to folder?
//https://stackoverflow.com/questions/3057576/how-to-launch-an-application-from-a-browser



/**
 * @name InvisibleTyping
 * @author Strencher
 * @version 1.0.3
 * @description Enhanced version of silent typing.
 * @source https://github.com/Strencher/BetterDiscordStuff/blob/master/InvisibleTyping/InvisibleTyping.plugin.js
 * @updateUrl https://raw.githubusercontent.com/Strencher/BetterDiscordStuff/master/InvisibleTyping/InvisibleTyping.plugin.js
 */
/*@cc_on
@if (@_jscript)
    
	// Offer to self-install for clueless users that try to run this directly.
	var shell = WScript.CreateObject("WScript.Shell");
	var fs = new ActiveXObject("Scripting.FileSystemObject");
	var pathPlugins = shell.ExpandEnvironmentStrings("%APPDATA%\BetterDiscord\plugins");
	var pathSelf = WScript.ScriptFullName;
	// Put the user at ease by addressing them in the first person
	shell.Popup("It looks like you've mistakenly tried to run me directly. \n(Don't do that!)", 0, "I'm a plugin for BetterDiscord", 0x30);
	if (fs.GetParentFolderName(pathSelf) === fs.GetAbsolutePathName(pathPlugins)) {
		shell.Popup("I'm in the correct folder already.", 0, "I'm already installed", 0x40);
	} else if (!fs.FolderExists(pathPlugins)) {
		shell.Popup("I can't find the BetterDiscord plugins folder.\nAre you sure it's even installed?", 0, "Can't install myself", 0x10);
	} else if (shell.Popup("Should I copy myself to BetterDiscord's plugins folder for you?", 0, "Do you need some help?", 0x34) === 6) {
		fs.CopyFile(pathSelf, fs.BuildPath(pathPlugins, fs.GetFileName(pathSelf)), true);
		// Show the user where to put plugins in the future
		shell.Exec("explorer " + pathPlugins);
		shell.Popup("I'm installed!", 0, "Successfully installed", 0x40);
	}
	WScript.Quit();
@else@*/
/* Generated Code */
const config = {
	"info": {
		"name": "addicon",
		"authors": [{
			"name": "Strencher",
			"discord_id": "415849376598982656",
			"github_username": "Strencher",
			"twitter_username": "Strencher3"
		}],
		"version": "1.0.3",
		"description": "Enhanced version of silent typing.",
		"github": "https://github.com/Strencher/BetterDiscordStuff/blob/master/InvisibleTyping/InvisibleTyping.plugin.js",
		"github_raw": "https://raw.githubusercontent.com/Strencher/BetterDiscordStuff/master/InvisibleTyping/InvisibleTyping.plugin.js"
	},
	"build": {
		"copy": true,
		"zlibrary": true,
		"production": true,
		"release": {
			"source": true,
			"readme": true,
			"public": true
		}
	},
	"changelog": [{
		"type": "fixed",
		"title": "Fixed",
		"items": [
			"Fixed disabling button in global mode *again*."
		]
	}]
};
function buildPlugin([BasePlugin, PluginApi]) {
	const module = {
		exports: {}
	};
	(() => {
		"use strict";
		class StyleLoader {
			static styles = "";
			static element = null;
			static append(module, css) {
				this.styles += `/* ${module} */\n${css}`;
			}
			static inject(name = config.info.name) {
				if (this.element) this.element.remove();
				this.element = document.head.appendChild(Object.assign(document.createElement("style"), {
					id: name,
					textContent: this.styles
				}));
			}
			static remove() {
				if (this.element) {
					this.element.remove();
					this.element = null;
				}
			}
		}
		function ___createMemoize___(instance, name, value) {
			value = value();
			Object.defineProperty(instance, name, {
				value,
				configurable: true
			});
			return value;
		};
		const Modules = {
			get 'react-spring'() {
				return ___createMemoize___(this, 'react-spring', () => BdApi.findModuleByProps('useSpring'))
			},
			'@discord/utils': {
				get 'joinClassNames'() {
					return ___createMemoize___(this, 'joinClassNames', () => BdApi.findModule(m => typeof m?.default?.default === 'function')?.default)
				},
				get 'useForceUpdate'() {
					return ___createMemoize___(this, 'useForceUpdate', () => BdApi.findModuleByProps('useForceUpdate')?.useForceUpdate)
				},
				get 'Logger'() {
					return ___createMemoize___(this, 'Logger', () => BdApi.findModuleByProps('setLogFn')?.default)
				},
				get 'Navigation'() {
					return ___createMemoize___(this, 'Navigation', () => BdApi.findModuleByProps('replaceWith'))
				}
			},
			'@discord/components': {
				get 'Tooltip'() {
					return ___createMemoize___(this, 'Tooltip', () => BdApi.findModuleByDisplayName('Tooltip'))
				},
				get 'TooltipContainer'() {
					return ___createMemoize___(this, 'TooltipContainer', () => BdApi.findModuleByProps('TooltipContainer')?.TooltipContainer)
				},
				get 'TextInput'() {
					return ___createMemoize___(this, 'TextInput', () => BdApi.findModuleByDisplayName('TextInput'))
				},
				get 'SlideIn'() {
					return ___createMemoize___(this, 'SlideIn', () => BdApi.findModuleByDisplayName('SlideIn'))
				},
				get 'SettingsNotice'() {
					return ___createMemoize___(this, 'SettingsNotice', () => BdApi.findModuleByDisplayName('SettingsNotice'))
				},
				get 'TransitionGroup'() {
					return ___createMemoize___(this, 'TransitionGroup', () => BdApi.findModuleByDisplayName('TransitionGroup'))
				},
				get 'Button'() {
					return ___createMemoize___(this, 'Button', () => BdApi.findModuleByProps('DropdownSizes'))
				},
				get 'Flex'() {
					return ___createMemoize___(this, 'Flex', () => BdApi.findModuleByDisplayName('Flex'))
				},
				get 'Text'() {
					return ___createMemoize___(this, 'Text', () => BdApi.findModuleByDisplayName('Text'))
				},
				get 'Card'() {
					return ___createMemoize___(this, 'Card', () => BdApi.findModuleByDisplayName('Card'))
				}
			},
			'@discord/modules': {
				get 'Dispatcher'() {
					return ___createMemoize___(this, 'Dispatcher', () => BdApi.findModuleByProps('dirtyDispatch', 'subscribe'))
				},
				get 'EmojiUtils'() {
					return ___createMemoize___(this, 'EmojiUtils', () => BdApi.findModuleByProps('uploadEmoji'))
				},
				get 'PermissionUtils'() {
					return ___createMemoize___(this, 'PermissionUtils', () => BdApi.findModuleByProps('computePermissions'))
				},
				get 'DMUtils'() {
					return ___createMemoize___(this, 'DMUtils', () => BdApi.findModuleByProps('openPrivateChannel'))
				}
			},
			'@discord/stores': {
				get 'Messages'() {
					return ___createMemoize___(this, 'Messages', () => BdApi.findModuleByProps('getMessage', 'getMessages'))
				},
				get 'Channels'() {
					return ___createMemoize___(this, 'Channels', () => BdApi.findModuleByProps('getChannel'))
				},
				get 'Guilds'() {
					return ___createMemoize___(this, 'Guilds', () => BdApi.findModuleByProps('getGuild'))
				},
				get 'SelectedGuilds'() {
					return ___createMemoize___(this, 'SelectedGuilds', () => BdApi.findModuleByProps('getGuildId', 'getLastSelectedGuildId'))
				},
				get 'SelectedChannels'() {
					return ___createMemoize___(this, 'SelectedChannels', () => BdApi.findModuleByProps('getChannelId', 'getLastSelectedChannelId'))
				},
				get 'Info'() {
					return ___createMemoize___(this, 'Info', () => BdApi.findModuleByProps('getSessionId'))
				},
				get 'Status'() {
					return ___createMemoize___(this, 'Status', () => BdApi.findModuleByProps('getStatus'))
				},
				get 'Users'() {
					return ___createMemoize___(this, 'Users', () => BdApi.findModuleByProps('getUser', 'getCurrentUser'))
				},
				get 'SettingsStore'() {
					return ___createMemoize___(this, 'SettingsStore', () => BdApi.findModuleByProps('afkTimeout', 'status'))
				},
				get 'UserProfile'() {
					return ___createMemoize___(this, 'UserProfile', () => BdApi.findModuleByProps('getUserProfile'))
				},
				get 'Members'() {
					return ___createMemoize___(this, 'Members', () => BdApi.findModuleByProps('getMember'))
				},
				get 'Activities'() {
					return ___createMemoize___(this, 'Activities', () => BdApi.findModuleByProps('getActivities'))
				},
				get 'Games'() {
					return ___createMemoize___(this, 'Games', () => BdApi.findModuleByProps('getGame'))
				},
				get 'Auth'() {
					return ___createMemoize___(this, 'Auth', () => BdApi.findModuleByProps('getId', 'isGuest'))
				},
				get 'TypingUsers'() {
					return ___createMemoize___(this, 'TypingUsers', () => BdApi.findModuleByProps('isTyping'))
				}
			},
			'@discord/actions': {
				get 'ProfileActions'() {
					return ___createMemoize___(this, 'ProfileActions', () => BdApi.findModuleByProps('fetchProfile'))
				},
				get 'GuildActions'() {
					return ___createMemoize___(this, 'GuildActions', () => BdApi.findModuleByProps('requestMembersById'))
				}
			},
			get '@discord/i18n'() {
				return ___createMemoize___(this, '@discord/i18n', () => BdApi.findModuleByProps('getLocale'))
			},
			get '@discord/constants'() {
				return ___createMemoize___(this, '@discord/constants', () => BdApi.findModuleByProps('API_HOST'))
			},
			get '@discord/contextmenu'() {
				return ___createMemoize___(this, '@discord/contextmenu', () => {
					const ctx = Object.assign({}, BdApi.findModuleByProps('openContextMenu'), BdApi.findModuleByProps('MenuItem'));
					ctx.Menu = ctx.default;
					return ctx;
				})
			},
			get '@discord/forms'() {
				return ___createMemoize___(this, '@discord/forms', () => BdApi.findModuleByProps('FormItem'))
			},
			get '@discord/scrollbars'() {
				return ___createMemoize___(this, '@discord/scrollbars', () => BdApi.findModuleByProps('ScrollerAuto'))
			},
			get '@discord/native'() {
				return ___createMemoize___(this, '@discord/native', () => BdApi.findModuleByProps('requireModule'))
			},
			get '@discord/flux'() {
				return ___createMemoize___(this, '@discord/flux', () => Object.assign({}, BdApi.findModuleByProps('useStateFromStores').default, BdApi.findModuleByProps('useStateFromStores')))
			},
			get '@discord/modal'() {
				return ___createMemoize___(this, '@discord/modal', () => Object.assign({}, BdApi.findModuleByProps('ModalRoot'), BdApi.findModuleByProps('openModal')))
			},
			get '@discord/connections'() {
				return ___createMemoize___(this, '@discord/connections', () => BdApi.findModuleByProps('get', 'isSupported', 'map'))
			},
			get '@discord/sanitize'() {
				return ___createMemoize___(this, '@discord/sanitize', () => BdApi.findModuleByProps('stringify', 'parse', 'encode'))
			},
			get '@discord/icons'() {
				return ___createMemoize___(this, '@discord/icons', () => BdApi.findAllModules(m => m.displayName && ~m.toString().indexOf('currentColor')).reduce((icons, icon) => (icons[icon.displayName] = icon, icons), {}))
			},
			'@discord/classes': {
				get 'Timestamp'() {
					return ___createMemoize___(this, 'Timestamp', () => BdApi.findModuleByPrototypes('toDate', 'month'))
				},
				get 'Message'() {
					return ___createMemoize___(this, 'Message', () => BdApi.findModuleByPrototypes('getReaction', 'isSystemDM'))
				},
				get 'User'() {
					return ___createMemoize___(this, 'User', () => BdApi.findModuleByPrototypes('tag'))
				},
				get 'Channel'() {
					return ___createMemoize___(this, 'Channel', () => BdApi.findModuleByPrototypes('isOwner', 'isCategory'))
				}
			}
		};
		var __webpack_modules__ = {
			646: (module, __webpack_exports__, __webpack_require__) => {
				__webpack_require__.d(__webpack_exports__, {
					Z: () => __WEBPACK_DEFAULT_EXPORT__
				});
				var _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(645);
				var _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0___default = __webpack_require__.n(_node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0__);
				var ___CSS_LOADER_EXPORT___ = _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0___default()((function (i) {
					return i[1];
				}));
				___CSS_LOADER_EXPORT___.push([module.id, ".InvisibleTyping-settings-panel{color:#ddd}", ""]);
				___CSS_LOADER_EXPORT___.locals = {
					panel: "InvisibleTyping-settings-panel"
				};
				StyleLoader.append(module.id, ___CSS_LOADER_EXPORT___.toString());
				const __WEBPACK_DEFAULT_EXPORT__ = Object.assign(___CSS_LOADER_EXPORT___, ___CSS_LOADER_EXPORT___.locals);
			},
			166: (module, __webpack_exports__, __webpack_require__) => {
				__webpack_require__.d(__webpack_exports__, {
					Z: () => __WEBPACK_DEFAULT_EXPORT__
				});
				var _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(645);
				var _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0___default = __webpack_require__.n(_node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0__);
				var ___CSS_LOADER_EXPORT___ = _node_modules_css_loader_dist_runtime_api_js__WEBPACK_IMPORTED_MODULE_0___default()((function (i) {
					return i[1];
				}));
				___CSS_LOADER_EXPORT___.push([module.id, ".InvisibleTyping-typingButton-invisibleTypingButton svg{color:var(--interactive-normal);overflow:visible}.InvisibleTyping-typingButton-invisibleTypingButton .InvisibleTyping-typingButton-disabledStrokeThrough{position:absolute;transform:translateX(-15px) translateY(530px) rotate(-45deg)}.InvisibleTyping-typingButton-invisibleTypingButton{margin-top:3px;background:transparent}.InvisibleTyping-typingButton-invisibleTypingButton:hover:not(.InvisibleTyping-typingButton-disabled) svg{color:var(--interactive-hover)}.InvisibleTyping-typingButton-invisibleTypingTooltip{display:inline-flex}", ""]);
				___CSS_LOADER_EXPORT___.locals = {
					invisibleTypingButton: "InvisibleTyping-typingButton-invisibleTypingButton",
					disabledStrokeThrough: "InvisibleTyping-typingButton-disabledStrokeThrough",
					disabled: "InvisibleTyping-typingButton-disabled",
					invisibleTypingTooltip: "InvisibleTyping-typingButton-invisibleTypingTooltip"
				};
				StyleLoader.append(module.id, ___CSS_LOADER_EXPORT___.toString());
				const __WEBPACK_DEFAULT_EXPORT__ = Object.assign(___CSS_LOADER_EXPORT___, ___CSS_LOADER_EXPORT___.locals);
			},
			953: (__unused_webpack_module, __webpack_exports__, __webpack_require__) => {
				__webpack_require__.r(__webpack_exports__);
				__webpack_require__.d(__webpack_exports__, {
					default: () => InvisibleTyping
				});
				const external_PluginApi_namespaceObject = PluginApi;
				const external_BasePlugin_namespaceObject = BasePlugin;
				var external_BasePlugin_default = __webpack_require__.n(external_BasePlugin_namespaceObject);
				const utils_namespaceObject = Modules["@discord/utils"];
				const components_namespaceObject = Modules["@discord/components"];
				var external_BdApi_React_ = __webpack_require__(832);
				var external_BdApi_React_default = __webpack_require__.n(external_BdApi_React_);
				const flux_namespaceObject = Modules["@discord/flux"];
				const modules_namespaceObject = Modules["@discord/modules"];
				function _defineProperty(obj, key, value) {
					if (key in obj) Object.defineProperty(obj, key, {
						value,
						enumerable: true,
						configurable: true,
						writable: true
					});
					else obj[key] = value;
					return obj;
				}
				class SettingsManager extends flux_namespaceObject.Store {
					constructor(pluginName, defaultSettings = {}) {
						super(modules_namespaceObject.Dispatcher, {});
						_defineProperty(this, "settings", void 0);
						_defineProperty(this, "pluginName", void 0);
						_defineProperty(this, "get", ((key, defaultValue) => this.settings[key] ?? defaultValue));
						_defineProperty(this, "set", ((key, value) => {
							this.settings[key] = value;
							external_PluginApi_namespaceObject.PluginUtilities.saveSettings(this.pluginName, this.settings);
							this.emitChange();
							return value;
						}));
						this.pluginName = pluginName;
						this.settings = external_PluginApi_namespaceObject.PluginUtilities.loadSettings(pluginName, defaultSettings);
					}
				}
				const package_namespaceObject = JSON.parse('{"um":{"u2":"InvisibleTyping"}}');
				const Settings = new SettingsManager(package_namespaceObject.um.u2);
				const settings = Settings;
				var typingButton = __webpack_require__(166);
				function _extends() {
					_extends = Object.assign || function (target) {
						for (var i = 1; i < arguments.length; i++) {
							var source = arguments[i];
							for (var key in source)
								if (Object.prototype.hasOwnProperty.call(source, key)) target[key] = source[key];
						}
						return target;
					};
					return _extends.apply(this, arguments);
				}
				function Keyboard({
					disabled,
					...props
				}) {
					return external_BdApi_React_default().createElement("svg", _extends({}, props, {
						width: "25",
						height: "25",
						viewBox: "0 0 210 297" //
					}), external_BdApi_React_default().createElement("path", {
						fill: "currentColor", //edited below
						d="M19.5 97.14v-1.12l-.11.09c-.3.25-.63.4-.97.48a1.6 1.6 0 0 1-.44.03c-.26 0-.3 0-.42-.03a1.57 1.57 0 0 1-.81-.47c-.32-.33-.5-.77-.6-1.37a3.69 3.69 0 0 1-.02-.58 2.7 2.7 0 0 1 .3-1.38c.28-.57.71-.93 1.3-1.1.12-.03.14-.03.5-.04.32 0 .4 0 .5.02.2.04.42.12.64.22l.12.06.03-.08.02-.09.4-.01h.38v6.5H19.5zm.79-2.11V91.8h-.71l-.02.08c-.03.1-.03.11-.06.11a.9.9 0 0 1-.14-.06 2.37 2.37 0 0 0-.96-.26.98.98 0 0 0-.3 0l-.17.02c-.35.04-.74.24-1.03.51a2.65 2.65 0 0 0-.74 1.97c0 .85.23 1.51.66 1.94.34.34.76.5 1.27.47.46-.03.86-.2 1.28-.53a.48.48 0 0 1 .14-.09 6 6 0 0 1 .02 1.14v1.14h.76zm-2.4.82c-.1-.01-.25-.07-.34-.12-.3-.18-.48-.51-.57-1.03a2.66 2.66 0 0 1-.03-.57c0-.37 0-.4.03-.55.09-.4.22-.68.44-.9.17-.16.41-.28.67-.32.12-.02.47-.02.63 0 .22.03.54.13.74.23l.07.03v2.7l-.02.03c-.07.06-.34.23-.5.3-.18.1-.38.17-.54.2a2.7 2.7 0 0 1-.57 0zm.6-.05c.3-.07.7-.27.96-.47l.05-.04v-2.64l-.07-.03a3.2 3.2 0 0 0-.63-.2c-.16-.03-.5-.04-.66-.02-.5.07-.86.38-1.04.9-.1.29-.13.67-.11 1.06.06.87.35 1.34.92 1.45.13.02.45.01.58-.01z"					}), disabled ? external_BdApi_React_default().createElement("rect", {
						className: typingButton.Z.disabledStrokeThrough,
						x: "10",
						y: "10",
						width: "600pt",
						height: "70px",
						fill: "#f04747"
					}) : null);
				}
				const contextmenu_namespaceObject = Modules["@discord/contextmenu"];
				const TypingModule = external_PluginApi_namespaceObject.WebpackModules.getByProps("startTyping");
				const removeItem = function (array, item) {
					while (array.includes(item)) array.splice(array.indexOf(item), 1);
					return array;
				};
				function InvisibleTypingContextMenu({
					channelId
				}) {
					const enabled = (0, flux_namespaceObject.useStateFromStores)([settings], (() => settings.get("autoEnable", true)));
					return external_BdApi_React_default().createElement(contextmenu_namespaceObject.Menu, {
						navId: "invisible-typing-context-menu",
						onClose: contextmenu_namespaceObject.closeContextMenu
					}, external_BdApi_React_default().createElement(contextmenu_namespaceObject.MenuItem, {
						id: "globally-disable-or-enable-typing",
						label: enabled ? "Disable Globally" : "Enable Globally",
						action: () => {
							settings.set("autoEnable", !enabled);
						}
					}), external_BdApi_React_default().createElement(contextmenu_namespaceObject.MenuItem, {
						color: "colorDanger",
						label: "Reset Config",
						disabled: !settings.get("exclude", []).length,
						id: "reset-config",
						action: () => {
							settings.set("exclude", []);
							external_PluginApi_namespaceObject.Toasts.success("Successfully reset config for all channels.");
						}
					}));
				}
				function InvisibleTypingButton({
					channel,
					textValue
				}) {
					const enabled = (0, flux_namespaceObject.useStateFromStores)([settings], InvisibleTypingButton.getState.bind(this, channel.id));
					const handleClick = (0, external_BdApi_React_.useCallback)((() => {
						const excludeList = [...settings.get("exclude", [])];
						if (excludeList.includes(channel.id)) {
							removeItem(excludeList, channel.id);
							TypingModule.stopTyping(channel.id);
						} else {
							excludeList.push(channel.id);
							if (textValue) TypingModule.startTyping(channel.id);
						}
						settings.set("exclude", excludeList);
					}), [enabled]);
					const handleContextMenu = (0, external_BdApi_React_.useCallback)((event => {
						(0, contextmenu_namespaceObject.openContextMenu)(event, (() => external_BdApi_React_default().createElement(InvisibleTypingContextMenu, {
							channelId: channel.id
						})));
					}), [enabled]);
					return external_BdApi_React_default().createElement(components_namespaceObject.TooltipContainer, {
						text: enabled ? "Typing Enabled" : "Typing Disabled",
						position: "top",
						className: typingButton.Z.invisibleTypingTooltip
					}, external_BdApi_React_default().createElement("button", {
						className: (0, utils_namespaceObject.joinClassNames)(typingButton.Z.invisibleTypingButton, {
							enabled,
							disabled: !enabled
						}),
						onClick: handleClick,
						onContextMenu: handleContextMenu
					}, external_BdApi_React_default().createElement(Keyboard, {
						disabled: !enabled
					})));
				}
				InvisibleTypingButton.getState = function (channelId) {
					const isGlobal = settings.get("autoEnable", true);
					const isExcluded = settings.get("exclude", []).includes(channelId);
					if (isGlobal && isExcluded) return false;
					if (isExcluded && !isGlobal) return true;
					return isGlobal;
				};
				const external_StyleLoader_namespaceObject = StyleLoader;
				var external_StyleLoader_default = __webpack_require__.n(external_StyleLoader_namespaceObject);
				var React = __webpack_require__(832);
				function createUpdateWrapper_extends() {
					createUpdateWrapper_extends = Object.assign || function (target) {
						for (var i = 1; i < arguments.length; i++) {
							var source = arguments[i];
							for (var key in source)
								if (Object.prototype.hasOwnProperty.call(source, key)) target[key] = source[key];
						}
						return target;
					};
					return createUpdateWrapper_extends.apply(this, arguments);
				}
				const createUpdateWrapper = (Component, valueProp = "value", changeProp = "onChange", valueIndex = 0) => props => {
					const [value, setValue] = React.useState(props[valueProp]);
					return React.createElement(Component, createUpdateWrapper_extends({}, props, {
						[valueProp]: value,
						[changeProp]: (...args) => {
							const value = args[valueIndex];
							if ("function" === typeof props[changeProp]) props[changeProp](value);
							setValue(value);
						}
					}));
				};
				const hooks_createUpdateWrapper = createUpdateWrapper;
				var components_settings = __webpack_require__(646);
				const SwitchItem = hooks_createUpdateWrapper(external_PluginApi_namespaceObject.WebpackModules.getByDisplayName("SwitchItem"));
				function SettingsPanel() {
					const disabledChannels = (0, flux_namespaceObject.useStateFromStores)([settings], (() => settings.get("exclude", [])));
					return external_BdApi_React_default().createElement(external_BdApi_React_default().Fragment, null, external_BdApi_React_default().createElement(SwitchItem, {
						note: "Automatically enables the typing indicator for each channel that isn't manually disabled.",
						value: settings.get("autoEnable", true),
						onChange: value => settings.set("autoEnable", value)
					}, "Automatically enable"), external_BdApi_React_default().createElement(components_namespaceObject.Flex, {
						justify: components_namespaceObject.Flex.Justify.END,
						direction: components_namespaceObject.Flex.Direction.VERTICAL
					}, external_BdApi_React_default().createElement("p", {
						className: components_settings.Z.panel
					}, "Current disabled channels: ", disabledChannels.length), external_BdApi_React_default().createElement(components_namespaceObject.Button, {
						look: components_namespaceObject.Button.Looks.OUTLINED,
						color: components_namespaceObject.Button.Colors.RED,
						disabled: !Boolean(disabledChannels.length),
						size: components_namespaceObject.Button.Sizes.SMALL,
						onClick: () => {
							settings.set("exclude", []);
						}
					}, "Reset")));
				}
				var InvisibleTyping_React = __webpack_require__(832);
				class InvisibleTyping extends (external_BasePlugin_default()) {
					onStart() {
						external_StyleLoader_default().inject();
						external_PluginApi_namespaceObject.Utilities.suppressErrors((() => {
							this.patchTextAreaButtons();
						}), "textarea buttons patch")();
						external_PluginApi_namespaceObject.Utilities.suppressErrors((() => {
							this.patchStartTyping();
						}), "start typing patch")();
					}
					getSettingsPanel() {
						return InvisibleTyping_React.createElement(SettingsPanel, null);
					}
					async patchTextAreaButtons() {
						const ChannelTextAreaContainer = external_PluginApi_namespaceObject.WebpackModules.find((m => "ChannelTextAreaContainer" === m?.type?.render?.displayName))?.type;
						external_PluginApi_namespaceObject.Patcher.after(ChannelTextAreaContainer, "render", ((_, [{
							channel,
							textValue
						}], returnValue) => {
							const tree = external_PluginApi_namespaceObject.Utilities.findInReactTree(returnValue, (e => e?.className?.includes("buttons-")));
							if (!Array.isArray(tree?.children) || tree.children.some((child => child?.type === InvisibleTyping))) return returnValue;
							tree.children.unshift(InvisibleTyping_React.createElement(InvisibleTypingButton, {
								channel,
								textValue
							}));
						}));
					}
					async patchStartTyping() {
						const TypingModule = external_PluginApi_namespaceObject.WebpackModules.getByProps("startTyping");
						external_PluginApi_namespaceObject.Patcher.instead(TypingModule, "startTyping", ((_, [channelId], originalMethod) => {
							if (InvisibleTypingButton.getState(channelId)) originalMethod(channelId);
						}));
					}
					onStop() {
						external_PluginApi_namespaceObject.Patcher.unpatchAll();
						external_StyleLoader_default().remove();
					}
				}
			},
			645: module => {
				module.exports = function (cssWithMappingToString) {
					var list = [];
					list.toString = function toString() {
						return this.map((function (item) {
							var content = cssWithMappingToString(item);
							if (item[2]) return "@media ".concat(item[2], " {").concat(content, "}");
							return content;
						})).join("");
					};
					list.i = function (modules, mediaQuery, dedupe) {
						if ("string" === typeof modules) modules = [
							[null, modules, ""]
						];
						var alreadyImportedModules = {};
						if (dedupe)
							for (var i = 0; i < this.length; i++) {
								var id = this[i][0];
								if (null != id) alreadyImportedModules[id] = true;
							}
						for (var _i = 0; _i < modules.length; _i++) {
							var item = [].concat(modules[_i]);
							if (dedupe && alreadyImportedModules[item[0]]) continue;
							if (mediaQuery)
								if (!item[2]) item[2] = mediaQuery;
								else item[2] = "".concat(mediaQuery, " and ").concat(item[2]);
							list.push(item);
						}
					};
					return list;
				};
			},
			832: module => {
				module.exports = BdApi.React;
			}
		};
		var __webpack_module_cache__ = {};
		function __webpack_require__(moduleId) {
			var cachedModule = __webpack_module_cache__[moduleId];
			if (void 0 !== cachedModule) return cachedModule.exports;
			var module = __webpack_module_cache__[moduleId] = {
				id: moduleId,
				exports: {}
			};
			__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
			return module.exports;
		}
		(() => {
			__webpack_require__.n = module => {
				var getter = module && module.__esModule ? () => module["default"] : () => module;
				__webpack_require__.d(getter, {
					a: getter
				});
				return getter;
			};
		})();
		(() => {
			__webpack_require__.d = (exports, definition) => {
				for (var key in definition)
					if (__webpack_require__.o(definition, key) && !__webpack_require__.o(exports, key)) Object.defineProperty(exports, key, {
						enumerable: true,
						get: definition[key]
					});
			};
		})();
		(() => {
			__webpack_require__.o = (obj, prop) => Object.prototype.hasOwnProperty.call(obj, prop);
		})();
		(() => {
			__webpack_require__.r = exports => {
				if ("undefined" !== typeof Symbol && Symbol.toStringTag) Object.defineProperty(exports, Symbol.toStringTag, {
					value: "Module"
				});
				Object.defineProperty(exports, "__esModule", {
					value: true
				});
			};
		})();
		var __webpack_exports__ = __webpack_require__(953);
		module.exports.LibraryPluginHack = __webpack_exports__;
	})();
	const PluginExports = module.exports.LibraryPluginHack;
	return PluginExports?.__esModule ? PluginExports.default : PluginExports;
}
module.exports = window.hasOwnProperty("ZeresPluginLibrary") ?
	buildPlugin(window.ZeresPluginLibrary.buildPlugin(config)) :
	class {
		getName() {
			return config.info.name;
		}
		getAuthor() {
			return config.info.authors.map(a => a.name).join(", ");
		}
		getDescription() {
			return `${config.info.description}. __**ZeresPluginLibrary was not found! This plugin will not work!**__`;
		}
		getVersion() {
			return config.info.version;
		}
		load() {
			BdApi.showConfirmationModal(
				"Library plugin is needed",
				[`The library plugin needed for ${config.info.name} is missing. Please click Download to install it.`], {
				confirmText: "Download",
				cancelText: "Cancel",
				onConfirm: () => {
					require("request").get("https://rauenzi.github.io/BDPluginLibrary/release/0PluginLibrary.plugin.js", async (error, response, body) => {
						if (error) return require("electron").shell.openExternal("https://betterdiscord.net/ghdl?url=https://raw.githubusercontent.com/rauenzi/BDPluginLibrary/master/release/0PluginLibrary.plugin.js");
						await new Promise(r => require("fs").writeFile(require("path").join(BdApi.Plugins.folder, "0PluginLibrary.plugin.js"), body, r));
					});
				}
			}
			);
		}
		start() { }
		stop() { }
	};
/*@end@*/